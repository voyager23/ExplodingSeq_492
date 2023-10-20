/*
 * iterator.cxx
 * 
 * Copyright 2023 mike <mike@Fedora37>
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
#include <iterator>
#include <vector>
#include <cstdint>


using u64 = uint64_t;
using u32 = uint32_t;
using namespace std;

int main(int argc, char **argv)
{
	vector<u32> aseq = {1, 19, 177, 1004, 907, 555, 94, 
	500, 514, 732, 544, 547, 577, 271, 413, 916, 897, 224, 1004};
	vector<u32>::iterator j;

	u32 a = *(prev(aseq.end(),1));	// last value pushed

	for(j = aseq.begin(); j != aseq.end(); ++j){
		if(*j == a) break;
	}		

	size_t d2 = distance(j, prev(aseq.end(),1));
	if(d2 == 0) {
		cout << "No matching value found." << endl;;
	} else {
		cout << "a:" << a <<"	distance: " << d2 << endl;
		// Assume n = 2000
		size_t d1 = distance(aseq.begin(),j);
		size_t offset = (2000 - d1) % d2;
		u32 an = *(next(j,offset));
		cout << "offset = " << offset << " a[n] = " << an << endl;
		
	}
	
	return 0;
}

