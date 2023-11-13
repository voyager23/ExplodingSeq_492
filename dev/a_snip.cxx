/*
 * a_snip.cxx
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
	const uint64_t p = 1091;
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
		cout << "i:" << i << " a:" << a << "\t";
	}while(a != a7);
	cout << "\norder:" << (i - 7) << endl;
	uint64_t order = (i - 7);
	uint64_t n = 72;
	uint64_t offset = ((n - 6) % order) - 1;
	cout << "offset:" << offset << endl;
	uint64_t target_idx = offset + 7;
	i = 7; a = a7;
	while(i != target_idx) {
		a = ((6*a*a + 10*a + 3) % p);
		i += 1;
	}
	cout << "a[" << n << "] = " << a << endl;
	
	return 0;
}

