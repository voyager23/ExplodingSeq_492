/*
 * cycle_length.cxx
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
#include <cstdint>
#include <vector>
#include <map>

using u64 = uint64_t;
using u32 = uint32_t;
using u128 = __uint128_t;
using namespace std;

int main(int argc, char **argv)
{
	// From modulus 1087 cycle length = 4
	//vector<u32> data = {1,19,185,673,285,1053,77,467,34,757,77,467}; // p = 1087
	vector<u32> data = {1,19,177,1004,907,555,94,500,514,732,544,547,577,271,413,916,897,224,1,19,177,1004}; // p = 1091


	vector<u32> clength = {1,19}; // Preload search vector
	u32 idx = 2;
	
	for(auto i = data.begin()+2; i != data.end(); ++i) {
		clength.push_back(*i);
		// does this entry already exist?
		for(vector<u32>::iterator j = clength.begin(); j != clength.end()-1; ++j){
			if(*j == clength.back()){
				cout << "cycle_length = " << (clength.end()-1 - j) << endl;
				goto label; // Jump to label
			}
		}
		cout << "Next check" << endl;
	}
// goto target
label:
	return 0;
}

