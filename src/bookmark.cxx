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
#include <unordered_map>
#include <climits>
#include <iterator>

#include "../inc/MillerRabin.hxx"

using u64 = uint64_t;
using u32 = uint32_t;
using u128 = __uint128_t;
using namespace std;

// Declarations
vector<u32>prime_modulus(u32 x, u32 y);
u64 simple_search(u32 x, u32 y, u64 n, u32 modulus = 0);
u64 bookmark_search(u32 x, u32 y, u64 n, u32 modulus = 0);
u64 map_search(u32 x, u32 y, u64 n, u32 modulus = 0);

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
		u32 a = 1;	u32 idx = 1;
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
u64 bookmark_search(u32 x, u32 y, u64 n, u32 modulus) {
	vector<u32> primes;
	if(modulus == 0) {
		primes = prime_modulus(x,y);
	} else {
		primes = {modulus};
	}
	//cout << "Bookmark search. Primes has " << primes.size() << " values." << endl;
	//cout << primes.front() << " -> " << primes.back() << endl;
	
	u64 B = 0;
	vector<u32>::iterator j;
	
	for(u32 &p : primes) {
		// setup the cycle length search
		vector<u32> aseq = {1,19}; // Preload search vector
		u32 a = 19;
		// calc and save next value of 'a'
		while(1){
			a = (6*a*a + 10*a + 3) % p;
			aseq.push_back(a);
			// a = *(prev(aseq.end(),1));	// last value pushed
			for(j = aseq.begin(); j != aseq.end(); ++j){
				if(*j == *(prev(aseq.end(),1))) break;
			}
			size_t d2 = distance(j, prev(aseq.end(),1));
			if(d2 == 0) {
				// cout << "No matching value found." << endl;;
				;
			} else {
				cout << "a:" << a <<"	distance: " << d2 << endl;
				size_t d1 = distance(aseq.begin(),j);
				size_t offset = ((2000 - d1) % d2) - 1; // offset correction
				u32 an = *(next(j,offset));				
				cout << "offset = " << offset << " a[n] = " << an << endl;
				goto NEXT_MODULUS;
			}
		} // while(1)...
	NEXT_MODULUS: ;
	} // next prime modulus
	return B;
}




//----------------------------------------------------------------------
u64 map_search(u32 x, u32 y, u64 n, u32 modulus) {
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
	unordered_map<u32,u64> amap; // key->a[n]  value->idx
	unordered_map<u32,u64>::iterator j;
	pair<unordered_map<u32,u64>::iterator, bool> result;
	
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
			a = 6*a*a + 10*a + 3;
			++idx;
			aseq.push_back(a);
			result = amap.emplace(a,idx);
			if (get<bool>(result) == true) continue;
			// assume a match has been found
			cout << "Match" << endl;
			j = get<0>(result);	// get the blocking iterator
			// find order, offset and final value from aseq
			size_t order = idx - get<size_t>(*j);
			size_t offset = (n - get<size_t(*j) + 1) % order;
			u32 an = aseq[get<size_t>(*j) + offset];
			cout "an = " << an << endl;
			B += an;
			goto NEXT_MODULUS;			
		} // while(1)...
		NEXT_MODULUS: ;
	} // next prime modulus
	return B;
}
//----------------------------------------------------------------------





//======================================================================

int main(int argc, char **argv)
{
	// Bookmark search
	const u32 x = 1e4;	//
	const u32 y = 1e3;  // 
	const u64 n = 2e3;	// 
	u64 B = 0;
	vector<u32> primes;
	cout << "Calc. vector of primes." << endl;
	primes = prime_modulus(x,y);
	for(u32 &p : primes){
	
		//cout << "Simple search"<< endl;	
		//B = simple_search(x,y,n,p);
		//cout << "Bookmark search" << endl;				
		//B = bookmark_search(x,y,n,p);
		cout << "Map_search" << endl;				
		B = map_search(x,y,n,p);

		cout << endl;
			
	}
	return 0;
}

