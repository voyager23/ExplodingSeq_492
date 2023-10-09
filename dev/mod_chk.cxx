/*
 * mod_chk.cxx
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
using u64 = uint64_t;
using u128 = __uint128_t;
using namespace std;

int main(int argc, char **argv)
{
	//~ vector<u64> moduli = {1000000007,1000000009,1000000021,1000000033,
		//~ 1000000087,1000000093,1000000097,1000000103,1000000123,
		//~ 1000000181,1000000207};
		
	vector<u64> moduli = {107};
	vector<u64> results = {};

	for(u64 &mod : moduli) {
		u64 a = 1;
		results.push_back(a);
		for(unsigned n = 2; n != 1001; ++n) {
			a = ((6*a*a) + (10*a) + 3) % mod;
			results.push_back(a);
		}
		cout << "a[1000]: mod " << mod << " = " << a << endl;
		for(u64 &r : results)
			cout << r << endl;
			
		// backward search
		u64 last_item = results.back();
		size_t cycle = 0;
		for(auto r = results.rbegin()+1; r != results.rend(); r++){
			cycle += 1;
			if (*r == last_item) {
				cout << "cycle length = " << results.size() - r << endl;
				break;
			}
		} 
	}
	return 0;
}

