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

//----------------------------------------------------------------------
vector<u64>prime_modulus(u64 x, u64 y){
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
u64 map_search(u64 x, u64 y, u64 n, u64 modulus) {
	typedef std::unordered_map<u64,u64> umap;
	std::vector<u64> primes;
	if(modulus == 0) {
		primes = prime_modulus(x,y);
	} else {
		primes = {modulus};
	}
	cout << "Map_search. Primes has " << primes.size() << " values." << endl;
	cout << primes.front() << " -> " << primes.back() << endl;
	// exit(0);	//DEBUG
	u64 B = 0;
	std::vector<u64> aseq;	// used to recover final value of a based on index
	umap amap; // key->a[n]  value->idx
	umap::iterator j;
	pair<umap::iterator, bool> result;
	
	u64 count = 0;
	for(u64 &p : primes) {
		// Preload vector of a values
		aseq.clear();
		aseq = {0,1,19};
		// Preload search map
		amap.clear();
		amap.emplace(1,1);
		amap.emplace(19,2);
		// extablish working variables
		u64 a = 19; size_t idx = 2;
		// iterate values of 'a'
		while(1){
			a = (6*a*a + 10*a + 3) % p;
			++idx;
			result = amap.emplace(a,idx);
			if (get<bool>(result) == true) {
				aseq.push_back(a);
				continue;
			}
			// match has been found
			//cout << "Match" << endl;
			size_t jidx = get<1>( *(get<0>(result)));
			size_t order = idx - jidx;
			size_t offset = (n - jidx + 1) % order;
			u64 an = aseq[jidx + offset - 1];
			cout << "a["<< n << "] mod " << p << " = " << an << "\torder: " << order << endl;
			B += an;
			
			if(++count > 20) exit(0);
			
			goto NEXT_MODULUS;			
		} // while(1)...
		NEXT_MODULUS: ;
	} // next prime modulus
	return B;
}
//----------------------------------------------------------------------

// Global

static const int num_threads = 4;

std::vector<uint64_t> primes;

// Thread data block
	typedef struct {
	size_t id;
	uint64_t n,result;
	std::vector<uint64_t>&v_prime = primes;
} tdb;
 
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
	for(size_t p = tdp->id; p < primes.size(); p += num_threads) {
		// Preload reverse map {imapa}
		a_seq.clear();
		a_seq = {0,1,19};
		// Preload search map {amapi}
		amapi.clear();
		amapi.emplace(0,0); 
		amapi.emplace(1,1); 
		amapi.emplace(19,2);
		// extablish working variables
		uint64_t a = 19;  uint64_t idx = 2;
		// iterate values of 'a'
		while(1){
			a = (6*a*a + 10*a + 3) % p;
			++idx;
			result = amapi.emplace(a,idx);
			if (get<bool>(result) == true) {
				a_seq.push_back(a);
				continue;
			} else { //found match for 'a'
				size_t jidx = get<1>( *(get<0>(result)));
				size_t order = idx - jidx;
				size_t offset = (tdp->n - jidx + 1) % order;
				u64 an = a_seq[jidx + offset - 1];
				//cout << "a["<< n << "] mod " << p << " = " << an << "\torder: " << order << endl;
				tdp->result += an;
				goto NEXT_MODULUS;
			}		
		} // while(1)...
	NEXT_MODULUS: ;
	}	 
}

//======================================================================
int main(int argc, char **argv) {
	
	// From modulus 1087 cycle length = 4
	//vector<u32> data = {1,19,185,673,285,1053,77,467,34,757,77,467}; // p = 1087
	//vector<u32> data = {1,19,177,1004,907,555,94,500,514,732,544,547,577,271,413,916,897,224,1,19,177,1004}; // p = 1091
	
	const uint64_t x = 1000;
	const uint64_t y =  200;

	primes = prime_modulus(x,y);
	std::vector<std::thread> vth;
	std::array<tdb, num_threads> atdb;

	 //Launch a team of threads
	 for (size_t i = 0; i < num_threads; ++i) {
		 // setup a thread data block
		 tdb *p = atdb.data() + i;
		 p->id = i; p->n = 1e5; p->result = 0;
		 
		 // setup a thread
		 //vth.push_back(std::thread(thread_map_search, p));
	 }
	exit(0);
	 // std::cout << "Launched from the main\n";

	 //Join the threads with the main thread
	 //for( auto i = vth.begin(); i != vth.end(); i++) i->join();
	 
	 // Scan/print the tdb array
	 for(auto i = 0; i < num_threads; ++i){
		 cout << atdb[i].id << " " << atdb[i].result << endl;
	 }

	 return 0;
 }
