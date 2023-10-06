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
using namespace std;

int main(int argc, char **argv)
{
	uint64_t a = 1;
	const uint64_t modulus = 1000000007;
	unsigned i;
	cout << a << "  " << a % modulus << endl;
	for(i = 2; i != 7; ++i) {
		a = 6*a*a + 10*a + 3;
		cout << a << "  " << a % modulus << endl;
	}
	a = 1;
	cout << a << "  " << a % modulus << endl;
	for(i = 2; i != 7; ++i) {
		a = ((6*a*a)%modulus + (10*a)%modulus + 3) % modulus;
		cout << a  << endl;
	}
	
	return 0;
}

