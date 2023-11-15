/*
 * b_snip.cxx
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
#include <cstdint>

using namespace std;

int main(int argc, char **argv)
{
	// Input Parameters
	//~ const uint64_t p = 1091;
	//~ const uint64_t p = 2137;
	
	const uint64_t p = 10459;
	const uint64_t n = 1000000000;
	// record intermediate stages of the order search
	vector<uint64_t> state = {0};	
	uint64_t a = 1;
	uint64_t i = 1;
	uint64_t a7 = 1;
	// calc the value of a7
	while(i != 7) {
		a7 = (6*a7*a7 + 10*a7 + 3) % p;
		i += 1;
		// debug print
		cout << "i:" << i << " a:" << a7 << "\t";
	}
	// Determine the order of the finite field
	a = a7; i = 7;
	do{
		a = (6*a*a + 10*a + 3) % p;
		i += 1;
		if((i % 100)==0) state.push_back(a);	// state for i=100 will be in slot 1 etc...
		cout << "i:" << i << " a:" << a << "\t";
	}while(a != a7);
	uint64_t order = (i - 7);
	cout << "\norder:" << (i - 7) << endl;
	// Determine the target index
	uint64_t offset = ((n - 6) % order) - 1;
	uint64_t target_idx = offset + 7;
	cout << "target index:" << target_idx << endl;
	
	i = 7; a = a7;
	while(i != target_idx) {
		a = ((6*a*a + 10*a + 3) % p);
		i += 1;
	}
	cout << "Predicted \ta[" << n << "] = " << a << endl;
	
	// Use state vector to find result
	a = state[target_idx / 100];
	i = ((target_idx / 100) * 100);
	while(i != target_idx){
		a = ((6*a*a + 10*a + 3) % p);
		i += 1;
	}
	cout << "Derived from state vector \ta[" << n << "] = " << a << endl;
	
	// confirm with a simple_search
	i = 1; a = 1;
	while(i != n) {
		a = ((6*a*a + 10*a + 3) % p);
		i += 1;
	}
	cout << "Simple search" << "\t";
	cout << "a[" << n << "] = " << a << endl;
		
	
	return 0;
}

