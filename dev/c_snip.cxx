/*
 * c_snip.cxx
 * 
 * Copyright 2023 Mike <mike@fedora38-2.home>
 */

#include <iostream>
#include <vector>
#include <cstdint>
#include <climits>
#include "../inc/MillerRabin.hxx"
using namespace std;

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

int main(int argc, char **argv)
{
	// Input Parameters
	//~ const uint64_t p = 1091;
	//~ const uint64_t p = 2137;
	
	const uint64_t x = 1e9;
	const uint64_t y = 5e3;
	const uint64_t n = 1e15;
	vector<uint64_t> primes;
	
	// state vector records intermediate stages of the search
	vector<uint64_t> state = {0};

	cout << "Calculating primes..." << endl;
	primes = prime_modulus(x,y);
	
	
	for(uint64_t &p : primes) {
		cout << "modulus: " << p << endl;
		uint64_t a = 1;
		uint64_t i = 1;
		uint64_t a7 = 1;
		// calc the value of a7
		while(i != 7) {
			a7 = (6*a7*a7 + 10*a7 + 3) % p;
			i += 1;
		}
		// Determine the order of the finite field
		state.clear();
		a = a7; i = 7;
		do{
			a = (6*a*a + 10*a + 3) % p;
			i += 1;
			if((i % 100)==0) state.push_back(a);	// state for i=100 will be in slot 1 etc...
			//~ cout << "i:" << i << " a:" << a << "\t";
		}while(a != a7);
		uint64_t order = (i - 7);
		cout << "order:" << (i - 7) << "  ";
		// Determine the target index
		uint64_t offset = ((n - 6) % order) - 1;
		uint64_t target_idx = offset + 7;
		cout << "target index:" << target_idx << endl;
		
		// Use state vector to find result
		a = state[target_idx / 100];
		i = ((target_idx / 100) * 100);
		while(i != target_idx){
			a = ((6*a*a + 10*a + 3) % p);
			i += 1;
		}
		cout << "Derived from state vector \ta[" << n << "] = " << a << endl << endl;
	}
		
	return 0;
}

