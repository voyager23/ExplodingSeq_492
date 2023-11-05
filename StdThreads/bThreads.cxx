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
static const int num_threads = 10;

// Thread data block
	typedef struct {
	size_t index;
	uint64_t x,y,n,result;
} TDB;	 
//----------------------------------------------------------------------

void a_func_thread(TDB *tdp) {
	//This function called from thread
	//std::cout << " id: " << tdp->index << std::endl;
	tdp->result = tdp->index * 100 + 1;
}

//======================================================================
int main(int argc, char **argv) {
	
	std::vector<uint64_t> primes = {2,3,5,7,11,13,17,19,23,29,31,37}; // 12 values
	std::vector<std::thread> vth;
	std::array<TDB, num_threads> atdb;

	 //Launch a group of threads
	 vth.clear();
	 
	 for (uint64_t i = 0; i < num_threads; ++i) {
		 // setup thread data block
		 TDB *p = atdb.data() + i;
		 p->index = i; p->n = 1e5; p->result = 0; p->x = 1e3; p->y = 1e2;
		 // setup thread
		 vth.push_back(std::thread(a_func_thread, p));
	 }

	 // std::cout << "Launched from the main\n";

	 //Join the threads with the main thread
	 for( auto i = vth.begin(); i != vth.end(); i++) i->join();
	 
	 // Scan/print the TDB array
	 for(auto i = 0; i < num_threads; ++i){
		 cout << atdb[i].index << " " << atdb[i].result << endl;
	 }

	 return 0;
 }
