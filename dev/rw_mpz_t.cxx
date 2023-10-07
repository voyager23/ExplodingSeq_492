/*
 * rw_mpz_t.cxx
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
#include <fstream>
#include <cstdint>
#include <gmpxx.h>

using namespace std;
int main(int argc, char **argv)
{
	mpz_class a, b, c;

	a = 1000001001;
	b = "-5678";
	c = a+b;

	ofstream fout;
	fout.open ("c++_mpz", ios::out|ios::binary);
	fout << a;
	fout << b;
	fout << c;
	fout.close();

	cout << "a:" << a << endl;
	cout << "b:" << b << endl;
	cout << "c:" << c << endl;
	cout << "a+b is " << c << "\n";
	cout << "absolute value is " << abs(c) << "\n";

	ifstream fin;
	uint32_t size;
	fin.open("c++_mpz", ios::in|ios::binary);
	while(fin >> a) {
		cout << a << endl;
	}
	fin.close();
	
  return 0;
}

