/*
 * test_malloc.cxx
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
#include <cstdlib>
#include <cstdint>
#include <array>

using namespace std;

int main(int argc, char **argv)
{
	array<uint64_t, 505000000> A;
	//~ uint64_t *ptr = (uint64_t *)malloc(505*1e6*sizeof(uint64_t));
	//~ if (ptr == NULL){
		//~ std::cout << "Fail\n";
	//~ } else {
		//~ std::cout << (((505*1000000) + 128)*sizeof(uint64_t)) << "	Succeded.\n";
	//~ }
	
	//~ uint64_t *foo = ptr+1000000;
	//~ *foo = 123456;
	
	
	
	//~ free(ptr);
	
	A[123456] = 654321;
	cout << A[123456] << " " << A[123457] << endl;
	
	
	return 0;
}

