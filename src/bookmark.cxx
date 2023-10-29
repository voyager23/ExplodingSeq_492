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
vector<u64>prime_modulus(u64 x, u64 y);
u64 simple_search(u64 x, u64 y, u64 n, u64 modulus = 0);
u64 bookmark_search(u64 x, u64 y, u64 n, u64 modulus = 0);
u64 map_search(u64 x, u64 y, u64 n, u64 modulus = 0);

// Definitions
vector<u64>prime_modulus(u64 x, u64 y){
	// approx 25 seconds for x=10^9 and y=10^7 returns 482449 values
	vector<u64> primes = {};
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
u64 simple_search(u64 x, u64 y, u64 n, u64 modulus) {
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
u64 bookmark_search(u64 x, u64 y, u64 n, u64 modulus) {
	vector<u64> primes;
	if(modulus == 0) {
		primes = prime_modulus(x,y);
	} else {
		primes = {modulus};
	}
	//cout << "Bookmark search. Primes has " << primes.size() << " values." << endl;
	//cout << primes.front() << " -> " << primes.back() << endl;
	
	u64 B = 0;
	vector<u64>::iterator j;
	
	for(u64 &p : primes) {
		// setup the cycle length search
		vector<u64> aseq = {1,19}; // Preload search vector
		u64 a = 19;
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
				u64 an = *(next(j,offset));				
				cout << "offset = " << offset << " a[n] = " << an << endl;
				goto NEXT_MODULUS;
			}
		} // while(1)...
	NEXT_MODULUS: ;
	} // next prime modulus
	return B;
}

u64 map_search(u64 x, u64 y, u64 n, u64 modulus) {
	typedef unordered_map<u64,u64> umap;
	vector<u64> primes;
	if(modulus == 0) {
		primes = prime_modulus(x,y);
	} else {
		primes = {modulus};
	}
	cout << "Map_search. Primes has " << primes.size() << " values." << endl;
	cout << primes.front() << " -> " << primes.back() << endl;
	// exit(0);	//DEBUG
	u64 B = 0;
	vector<u64> aseq;	// used to recover final value of a based on index
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

//======================================================================

int main(int argc, char **argv)
{
	// Bookmark search
	const u64 x = 1e9;	//
	const u64 y = 1e4;  // 
	const u64 n = 1e3;	// 
	u64 B = 0;
	//cout << "Simple search"<< endl;	
	//B = simple_search(x,y,n);
	
	//~ cout << "Bookmark search" << endl;				
	//~ B = bookmark_search(x,y,n,p);
	
	B = 0;
	cout << "Map_search" << endl;
	B += map_search(x,y,1e15);
	
	cout << "B() = " << B << endl;
	
	return 0;
}

