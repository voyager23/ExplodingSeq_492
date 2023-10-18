/*
 * bookmark.cxx
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
#include <climits>

#include "../inc/MillerRabin.hxx"

using u64 = uint64_t;
using u32 = uint32_t;
using u128 = __uint128_t;
using namespace std;

// Declarations
vector<u32>prime_modulus(u32 x, u32 y);
u64 simple_search(u32 x, u32 y, u64 n);


const u32 foobar = 1031;

// Definitions

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
//----------------------------------------------------------------------
u64 simple_search(u32 x, u32 y, u64 n) {
	//vector<u32> primes = prime_modulus(x,y);
	vector<u32> primes = {1091};
	cout << "Simple search. Primes has " << primes.size() << " values." << endl;
	cout << primes.front() << " -> " << primes.back() << endl;
	u64 B = 0;
	for(u32 &p : primes) {
		u32 a = 1;	u32 idx = 1;
		while(idx < n) {
			idx += 1;
			a = (6*a*a + 10*a + 3) % p;
			cout << idx << ": " << a << endl;
		} // while...
		cout << "a["<< n << "] mod " << p << " = " << a <<endl<<endl;;
		B = (B + a);
	} // for...
	return B;
}

//----------------------------------------------------------------------
u64 bookmark_search(u32 x, u32 y, u64 n) {
	vector<u32> primes = prime_modulus(x,y);
	//vector<u32> primes = {157,497};
	cout << "Bookmark search. Primes has " << primes.size() << " values." << endl;
	cout << primes.front() << " -> " << primes.back() << endl;
	
	u64 B = 0;
	
	for(u32 &p : primes) {
		map<u32,u32> cycles = { make_pair(1,1), make_pair(19,2) };
		u32 a = 19; u32 idx = 2;
		do {
			a = (6*a*a + 10*a + 3) % p;
			idx += 1;
			auto result = cycles.emplace(make_pair(a,idx));
			if (result.second == false) {
				//TODO
			}
		} while (1);			
	}
	return B;
}

//======================================================================

int main(int argc, char **argv)
{
	// Bookmark search
	const u32 x = 1e3; 	// 1000
	const u32 y = 1e3;   // 1000
	const u64 n = 2e3;	// 2000
	u64 B = 0;
	
	
	B = simple_search(x,y,n);
	cout << "Simple search => " << B << endl;
			
	//~ B = bookmark_search(x,y,n);
	//~ cout << "Bookmark search => " << B << endl;			
	
	return 0;
}

