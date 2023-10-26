/*
 * checkMillerRabin.cxx
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
#include <set>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <climits>
#include "../inc/MillerRabin.hxx"

using u64 = uint64_t;
using u32 = uint32_t;
using namespace std;

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
u64 simple_search(u32 x, u32 y, u64 n, u32 modulus) {
	vector<u32> primes;
	if(modulus == 0) {
		primes = prime_modulus(x,y);
	} else {
		primes = {modulus};
	}
	//cout << "Simple search. Primes has " << primes.size() << " values." << endl;
	//cout << primes.front() << " -> " << primes.back() << endl;
	u64 B = 0;
	for(u32 &p : primes) {
		u32 a = 1;	u64 idx = 1;
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

u64 map_search(u32 x, u32 y, u64 n, u32 modulus) {
	typedef unordered_map<u32,u64> umap;
	vector<u32> primes;
	if(modulus == 0) {
		primes = prime_modulus(x,y);
	} else {
		primes = {modulus};
	}
	//cout << "Bookmark search. Primes has " << primes.size() << " values." << endl;
	//cout << primes.front() << " -> " << primes.back() << endl;
	
	u64 B = 0;
	vector<u32> aseq;	// used to recover final value of a based on index
	umap amap; // key->a[n]  value->idx
	umap::iterator j;
	pair<umap::iterator, bool> result;
	
	for(u32 &p : primes) {
		// Preload vector of a values
		aseq.clear();
		aseq = {0,1,19};
		// Preload search map
		amap.clear();
		amap.emplace(1,1);
		amap.emplace(19,2);
		// extablish working variables
		u32 a = 19; size_t idx = 2;
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
			u32 an = aseq[jidx + offset - 1];
			cout << "a["<< n << "] mod " << p << " = " << an <<endl;
			B += an;
			goto NEXT_MODULUS;			
		} // while(1)...
		NEXT_MODULUS: ;
	} // next prime modulus
	return B;
}

int main(int argc, char **argv)
{
	set<uint32_t> primes ={1000000007,1000000009,1000000021,1000000033,
		1000000087,1000000093,1000000097,1000000103,1000000123,1000000181,
		1000000207,1000000223,1000000241,1000000271,1000000289,1000000297,1000000321,1000000349,1000000363,1000000403,
		1000000409,1000000411,1000000427,1000000433,1000000439,1000000447,1000000453,1000000459,1000000483,1000000513,
		1000000531,1000000579,1000000607,1000000613,1000000637,1000000663,1000000711,1000000753,1000000787,1000000801,
		1000000829,1000000861,1000000871,1000000891,1000000901,1000000919,1000000931,1000000933,1000000993};
		
	uint64_t B = 0;
	//uint32_t modulus = 1000000613;
	uint64_t n = 1e3;
	
	for(auto &p : primes) 
		B += simple_search(1e9, 1e3, n, p );
	
	cout << "Simple search B = " << B << endl;



	//~ B = map_search(1e9, 1e3, n, modulus );
	//~ cout << "Map search Modulus = " << modulus << " B = " << B << endl;
	
	return 0;
}

