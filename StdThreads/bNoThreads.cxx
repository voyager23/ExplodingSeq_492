 #include <iostream>
 #include <thread>
 #include <unordered_map>
 #include <vector>
 #include <array>
 #include <cstdint>
 #include <climits>
 #include "../inc/MillerRabin.hxx"
 
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = __uint128_t;

// Globals
static const int num_threads = 1;
std::vector<uint64_t> primes;	// Referenced in Thread data block
// Thread data block
typedef struct {
	size_t id;
	uint64_t n,result;
	std::vector<uint64_t>&v_prime = primes;
}tdb;
// Declarations
vector<u64> prime_modulus(u64 x, u64 y);
u64 map_search(u64 x, u64 y, u64 n, u64 modulus);
void thread_map_search(tdb *tdp);
u64 simple_search(u64 x, u64 y, u64 n);

// Definitions
vector<u64> prime_modulus(u64 x, u64 y){
	// approx 25 seconds for x=10^9 and y=10^7 returns 482449 values
	std::vector<u64> primes = {};
	if((x % 2)==0) x += 1; // test odd values
	for(u64 p = x; p <= x+y; p+=2) {
		if (MillerRabin(p)) {
			if(p <= UINT_MAX){
				primes.push_back(p);
			} else {
			cout << "Warning: prime_modulus overflow" << endl;
			}
		}
	}
	return primes;
}
//----------------------------------------------------------------------

void thread_map_search(tdb *tdp) {
	// Calculate the value of a{n} for a range of moduli.
	// Sum each value to result variable.
	// map values of 'a' to their respective idx
	std::unordered_map<uint64_t, uint64_t> amapi;
	// vector of sequential values of 'a' to enable recovery of the first index instance 
	std::vector<uint64_t> a_seq;
	pair<std::unordered_map<uint64_t, uint64_t>::iterator, bool> result;	// emplace return value
	
	tdp->result = 0;
	for(size_t p = tdp->id; p < tdp->v_prime.size(); p += num_threads) {
		// Preload reverse map {imapa}
		a_seq.clear();
		a_seq = {0,1,19};
		// Preload search map {amapi}
		amapi.clear();
		amapi.emplace(0,0); 
		amapi.emplace(1,1); 
		amapi.emplace(19,2);
		cout << 0 << endl << 1 << endl << 19 << endl;
		// extablish working variables
		uint64_t a = 19;  uint64_t idx = 2;
		// iterate values of 'a'
		while(1){
			a = (6*a*a + 10*a + 3) % tdp->v_prime[p];
			++idx;
			result = amapi.emplace(a,idx);
			if (get<bool>(result) == true) {
				a_seq.push_back(a);
				cout << a << endl;
				continue;
			} else { //found match for 'a'
				cout << a << endl;
				size_t jidx = get<1>( *(get<0>(result)));
				size_t order = idx - jidx - 1;
				size_t offset = (tdp->n - jidx + 1) % order;
				u64 an = a_seq[jidx + offset - 1];
				cout << "\na[no_limit] mod " << tdp->v_prime[p] << " = " << an << "\torder: " << order << endl;
				tdp->result += an;
				goto NEXT_MODULUS;	// Jump to next prime modulus
			}		
		} // while(1)...
	NEXT_MODULUS: ;
	}	 
}
// ---------------------------------------------------------------------

u64 simple_search(u64 x, u64 y, u64 n) {
	vector<u64> primes = prime_modulus(x,y);
	primes = {1021};
	cout << "Simple search. Primes has " << primes.size() << " values." << endl;
	cout << primes.front() << " -> " << primes.back() << endl;
	u64 B = 0;
	for(u64 &p : primes) {
		u64 a = 1;	u64 idx = 1;
		while(idx < n) {
			idx += 1;
			a = (6*a*a + 10*a + 3) % p;
		} // while...
		cout << "simple search a[n] = " << a << " % " << p << endl;
		B = (B + a);
	} // for...
	return B;
}

//======================================================================
int main(int argc, char **argv) {
	
	
	const uint64_t x = 1000;
	const uint64_t y =  200; // This gives 29 primes

	primes = prime_modulus(x,y);
	
	primes = {1021};	// a[n] = 
	
	std::vector<std::thread> vth;
	std::array<tdb, num_threads> atdb;

	 //Launch a team of threads
	 for (size_t i = 0; i < num_threads; ++i) {
		 // setup a thread data block
		 tdb *p = atdb.data() + i;
		 p->id = i; p->n = 1e5; p->result = 0;
		 
		 // setup a thread
		 // vth.push_back(std::thread(thread_map_search, p));
		 thread_map_search(p);
	 }
	 //std::cout << "Launched from the main\n";

	 //Join the threads with the main thread
	 //for( auto i = vth.begin(); i != vth.end(); i++) i->join();
	 
	 // Scan/print the tdb array
	 uint SUM = 0;
	 for(auto i = 0; i < num_threads; ++i){
		 //cout << atdb[i].id << " " << atdb[i].result << endl;
		 SUM += atdb[i].result;
	 }
	 cout << "Final sum: " << SUM << endl << endl;
	 
	 cout << simple_search(x,y,100000) << endl;

	 return 0;
 }
