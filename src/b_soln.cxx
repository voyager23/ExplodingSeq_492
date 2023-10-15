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
 * solution: 242586962923928 15 digits (uint64_t)
 */

//~ Notes: Except for the final sum B, integers can be contained in uint32_t
//~ which has a max value of 4,294,967,295 > 1,001,000,000.
//~ The value of a is always odd. This implies that the maximum number of a%p values
//~ will be 1,001,000,000 / 2, approx 505,000,000 values (worst case). This 
//~ can be reserved for a vector<uint32_t>. Alternatively use vector.clear() 
//~ which does not change capacity and allows dynamic resize.


#include <iostream>
#include <cstdint>
#include <vector>
#include <map>
#include <climits>

#include "../inc/MillerRabin.hxx"

using u64 = uint64_t;
using u32 = uint32_t;
using u128 = __uint128_t;
using namespace std;

vector<u32>prime_modulus(u32 x, u32 y);
vector<u32>prime_modulus(u32 x, u32 y){
	// approx 25 seconds for x=10^9 and y=10^7 returns 482449 values
	vector<u32> primes = {};
	if((x % 2)==0) x += 1; // test odd values
	for(u32 p = x; p <= x+y; p+=2) {
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

// Searches require a list/vector of prime moduli

u64 simple_search(u32 x, u32 y, u64 n);
u64 cyclic_search(u32 x, u32 y, u64 n);

// ---------------------------------------------------------------------
u64 simple_search(u32 x, u32 y, u64 n) {
	vector<u32> primes = prime_modulus(x,y);
	cout << "Simple search. Primes has " << primes.size() << " values." << endl;
	cout << primes.front() << " -> " << primes.back() << endl;
	u64 B = 0;
	for(u32 &p : primes) {
		u32 a = 1;	u32 idx = 1;
		while(idx < n) {
			idx += 1;
			a = (6*a*a + 10*a + 3) % p;
		} // while...
		B = (B + a);
	} // for...
	return B;
}

//----------------------------------------------------------------------
u64 cyclic_search(u32 x, u32 y, u64 n) {
	
	uint64_t *ptr = (uint64_t *)malloc(505*1e6*sizeof(uint64_t));
	if (ptr == NULL){
		std::cout << "Fail\n";
		exit(1);
	} else {
		std::cout << (((505*1000000) + 128)*sizeof(uint64_t)) << "	Succeded.\n";
	}
	
	vector<u32> primes = prime_modulus(x,y);
	cout << "Cyclic search. Primes has " << primes.size() << " values." << endl;
	cout << primes.front() << " -> " << primes.back() << endl;
	
	u64 B = 0;
	vector<u64> A;
	A.reserve(x/2);
	for(u32 &p : primes) {
		A.clear();
		A = {0,1,19};
		u64 a = 19;	size_t idx = 2;
		while(idx < 6) {
			idx += 1;
			a = (6*a*a + 10*a + 3) % p;
			A.push_back(a);
		}
		u64 a6 = a;	// Note value for repeat check
		do {
			a = (6*a*a + 10*a + 3) % p;
			idx += 1;
			A.push_back(a);
		}while (a != a6);
		size_t cycle_length = idx - 6;
		size_t result_idx = n % cycle_length;
		u64 a_n = A.at(result_idx);
		cout << a_n << "\tcycle: " << cycle_length << endl;
		B += a_n;
	}
	
	free(ptr);
	return B;
}

//----------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Example 2 (10^9, 10^3, 10^15)
	const u32 x = 1e9; 	// 10^9
	const u32 y = 1e3;  // 10^3
	const u64 n = 1e15;	// 10^15
	
	
	if(n < (x + y)) {
		u64 B = simple_search(x,y,n);
		cout << "Simple search => " << B << endl;
	} else {
		u64 B = 0;
		B = cyclic_search(x,y,n);
		cout << "Cyclic search => " << B << endl;		
	}
	
	return 0;
}

