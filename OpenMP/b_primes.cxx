/*
 * primes_example.cxx
 * 
 * Copyright 2023 Mike <mike@fedora38-2.home>
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
#include <vector>
#include <unordered_map>
#include <omp.h>
#include <iterator>
#include <utility>
#include "../inc/MillerRabin.hxx"

using u64 = uint64_t;
using u32 = uint32_t;
using namespace std;

// Definitions
vector<u64>prime_modulus(u64 x, u64 y){
	// approx 25 seconds for x=10^9 and y=10^7 returns 482449 values
	vector<u64> primes = {};
	if((x % 2)==0) x += 1; // test odd values
	for(u64 p = x; p <= x+y; p+=2) {
		if (MillerRabin(p)) {
				primes.push_back(p);
		}
	}
	return primes;
}

//----------------------------------------------------------------------

u64 simple_search(u64 x, u64 y, u64 n, u64 modulus = 11987) {
	vector<u64> primes;
	if(modulus == 0) {
		primes = prime_modulus(x,y);
	} else {
		primes = {modulus};
	}
	cout << "Simple search. Primes has " << primes.size() << " values." << endl;
	cout << primes.front() << " -> " << primes.back() << endl;
	
	u64 B = 0;
	for(u64 &p : primes) {
		u64 a = 1;	u64 idx = 1;
		while(idx < n) {
			idx += 1;
			a = (6*a*a + 10*a + 3) % p;
			//cout << idx << ": " << a << endl;
		} // while...
		cout << "a["<< n << "] mod " << p << " = " << a <<endl;
		B = (B + a);
	} // for...
	return B;
}

//----------------------------------------------------------------------

int main(int argc, char **argv)
{
	const u32 n = 100000;
	const u64 x = 1e4;
	const u64 y = 2e3;
	vector<u64> primes = prime_modulus(x, y);
	
	// Debug single value
	primes.clear();
	primes.push_back(10657);
	
	cout << "vector size: " << primes.size() << endl;
	u64 Sum = 0;
	for(auto &p : primes) Sum += p;
	cout << "Sum of vector: " << Sum << endl;
	
	//compute sum 
	u64 B = 0;
	u64 t1,t2;
	u32 a_n, idx;
	unordered_map<u32,u32> amap, imap;  
	unordered_map<u32,u32>::iterator j,k;
	std::pair<unordered_map<u32,u32>::iterator, bool> result;

	#pragma omp parallel private(amap, imap, j, k, t1, t2, a_n) shared(B) 
	{ 
		//the array is distributed statically between threads
		#pragma omp for schedule(static) 
			for (auto &p : primes) {
				// setup the cycle length search
				amap.clear();
				imap.clear();		
				amap.emplace(1,1);  // a_n -> idx
				imap.emplace(1,1);	// idx -> a_n
				amap.emplace(2,19);
				imap.emplace(19,2);
				a_n = 19; idx = 2;
				// calc and possibly save next value of 'a'
				while(1){
					t1 = a_n * a_n * 6;
					t2 = 10 * a_n;
					a_n = (u32)((t1 + t2 + 3) % p);
					++idx;
					result = amap.emplace(a_n, idx);
					if (result.second == true) {
						imap.emplace(idx, a_n);	// idx is unique (sequential)
						continue;
					} else { // matching value of a_n found.
						// recover the index
						k = result.first; //iterator to previous mapped pair < a_n, index >					
						u32 order = idx - (k->second);
						u32 offset = (n - (k->second) + 1) % order;
						a_n = imap[offset + k->second];
						#pragma omp critial
						B += a_n;
						goto NEXT_MODULUS;
					}
				}
		NEXT_MODULUS: ;		   
		} // for
	} // pragma
	cout << "#pragma B = " << B << endl;
	
	// Do simple search here with matching values for x,y and n
	
	cout << simple_search(x,y,n) << endl;
	
	return 0;
}

