/*
 * a_soln.cxx
 * 
 * Copyright 2023 mike <mike@fedora38-1.home>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */



#include <iostream>
#include <cstdint>
#include <vector>
#include <map>
#include "../inc/MillerRabin.hxx"

using u64 = uint64_t;
using u128 = __uint128_t;
using namespace std;

vector<u64>prime_modulus(u64 x, u64 y);
vector<u64>prime_modulus(u64 x, u64 y){
	// approx 25 seconds for x=10^9 and y=10^7 returns 482449 values
	vector<u64> primes = {};
	if((x % 2)==0) x += 1; // test odd values
	for(u64 p = x; p <= x+y; p+=2)
		if (MillerRabin(p)) primes.push_back(p);	
	return primes;
}

// Searches require a list/vector of prime moduli

u64 simple_search(u64 x, u64 y, u64 n);
u64 cyclic_search(u64 x, u64 y, u64 n);

// ---------------------------------------------------------------------
u64 simple_search(u64 x, u64 y, u64 n) {
	vector<u64> primes = prime_modulus(x,y);
	cout << "Simple search. Primes has " << primes.size() << " values." << endl;
	cout << primes.front() << " -> " << primes.back() << endl;
	u64 B = 0;
	for(u64 &p : primes) {
		u64 a = 1;	u64 idx = 1;
		while(idx < n) {
			idx += 1;
			a = (6*a*a + 10*a + 3) % p;
		} // while...
		B = (B + a);
	} // for...
	return B;
}

//----------------------------------------------------------------------
u64 cyclic_search(u64 x, u64 y, u64 n) {
	vector<u64> primes = prime_modulus(x,y);
	cout << "Cyclic search. Primes has " << primes.size() << " values." << endl;
	cout << primes.front() << " -> " << primes.back() << endl;
	// B = 0;
	// For each modulus
		// Establish the value of a{6}
		// Continue to record index and value of a{n} until a match is found.
		// cycle length is difference of indexes.
		// x mod p gives index of final value
		// sum to B
	u64 B = 0;
	for(u64 &p : primes) {
		u64 a = 1;	u64 idx = 1;
		while(idx < 6) {
			idx += 1;
			a = (6*a*a + 10*a + 3) % p;
		}
		u64 a6 = a;
		do {
			a = (6*a*a + 10*a + 3) % p;
			idx += 1;
		}while (a != a6);
		// debug
		cout << "idx-6 = " << idx - 6 << endl;
		// find iterations mod cycle length
		// this value is index to final value
		// debug
	}
		
	return 0;
}

//----------------------------------------------------------------------
int main(int argc, char **argv)
{
	const u64 x = 1000000000; // 10^9
	//const u64 y = 10000000; // 10^7
	const u64 y = 1000;  // 10^3
	const u64 n = 1000000000000;	 // 10^15  example 2.
	
try {
   std::vector<uint32_t> foo;
   foo.reserve(1000000000 + 10000000);
   foo = {0,1,19};
   foo.clear();
   cout << foo.capacity() << endl;
   foo[foo.capacity()-1] = 999999999;
}
catch(...) {
	cout << "Something failed" << endl;
	
}
	exit(0);
	
	//~ const u64 lo_prime =  1000000007;
	//~ const u64 mid_prime = 1000000993; // y = 10^3
	//~ const u64 hi_prime =  1009999999; // y = 10^7
	
	
	if(n < (x + y)) {
		u64 B = simple_search(x,y,n);
		cout << "Simple search => " << B << endl;
	} else {
		cyclic_search(x,y,n);
	}
	
	return 0;
}

