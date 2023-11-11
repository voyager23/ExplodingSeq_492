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
static const int num_threads = 8;
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
	std::unordered_map<uint64_t, uint64_t> map_empty = {};
	// vector of sequential values of 'a' to enable recovery of the first index instance 
	std::vector<uint64_t> a_seq;
	std::vector<uint64_t> seq_empty = {};
	pair<std::unordered_map<uint64_t, uint64_t>::iterator, bool> result;	// emplace return value
	
	tdp->result = 0;
	for(size_t p = tdp->id; p < tdp->v_prime.size(); p += num_threads) {
		// Preload reverse map {imapa}
		a_seq = seq_empty;
		a_seq = {0,1,19};
		// Preload search map {amapi}
		amapi = map_empty; 
		amapi.emplace(1,1); 
		amapi.emplace(19,2);
		//~ cout << 1 << endl << 19 << endl;
		// extablish working variables
		uint64_t a = 19;  uint64_t idx = 2;
		// iterate values of 'a'
		while(1){
			a = (6*a*a + 10*a + 3) % tdp->v_prime[p];
			++idx;
			result = amapi.emplace(a,idx);
			if (get<bool>(result) == true) {
				a_seq.push_back(a);
				//~ cout << a << endl;
				continue;
			} else { //found match for 'a'
				//~ cout << a << endl;
				size_t head = get<1>( *(get<0>(result)));
				size_t order = idx - head;
				int64_t offset = (tdp->n - (head - 1)); // allow for negative offset values
				offset %= order;
				offset -= 1;
				if(offset < 0) offset += order;
				//~ cout << head+offset << endl;
				//~ for(auto i = a_seq.begin(); i != a_seq.end(); ++i) cout << *i << " ";
				//~ cout << endl;
				u64 an = a_seq[head + offset];
				// cout << "a[100000] mod " << tdp->v_prime[p] << " = " << an << "\torder: " << order << endl;
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
	
	//primes ={1021};
			
	cout << "Simple search. Primes has " << primes.size() << " values." << endl;
	cout << primes.front() << " -> " << primes.back() << endl;

	u64 B = 0;
	for(u64 &p : primes) {
		u64 a = 1;	u64 idx = 1;
		while(idx < n) {
			idx += 1;
			a = (6*a*a + 10*a + 3) % p;
		} // while...
		//cout << "simple search a[100000] = " << a << " % " << p << endl;
		B = (B + a);
	} // for...
	return B;
}

//======================================================================
int main(int argc, char **argv) {
	
	//~ Example 2 killed due to lack of memory space
	
	const uint64_t x = 1000000000;			// 1e9
	const uint64_t y =  1000;				// 1e7
	const uint64_t n = 1000000000000000;	// 1e15

	cout << "Calculating primes..." << endl;
	primes = prime_modulus(x,y);
	cout << primes.size() << " primes. ";
	
	cout << primes.front() << " => " << primes.back() << endl;
	
	//~ cout << (2359*2359*6 + 2359*10 + 3) << endl;
	//~ exit(0);
	//~ // DEBUG END
	
	std::vector<uint64_t> aseq;
	for(auto p : primes) {
		aseq = {1,19,2359,33412879};
		uint64_t a = 33412879;
		uint64_t i = 4;
		// calc and push a[5]
		a = (6*a*a + 10*a + 3) % p;
		++i;
		aseq.push_back(a);
		// calc and push a[6]
		a = (6*a*a + 10*a + 3) % p;
		++i;
		aseq.push_back(a);
		
		do {
			a = (6*a*a + 10*a + 3) % p;
			aseq.push_back(a);
			i++;
		}while(aseq.back() != aseq.at(5));	// compare to a[6]
		
		for(auto b = aseq.begin(); b != aseq.begin() + 6; ++b)   cout << *b << " ";
		cout << "  <>  ";
		for(auto c = aseq.rbegin(); c != aseq.rbegin() + 6; ++c) cout << *c << " ";
		cout << " size: " << aseq.size() << endl;
		cout << "order:" << aseq.size()-6 << " modulus:" << p; 
		cout<<endl<<endl;;
	}
		
	 return 0;
 }