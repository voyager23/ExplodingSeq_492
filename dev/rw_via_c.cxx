/*
 * rw_via_c.cxx
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

	cout << "a:" << a << endl;
	cout << "b:" << b << endl;
	cout << "c:" << c << endl;
	cout << "a+b is " << c << "\n";
	cout << "absolute value is " << abs(c) << "\n";

	// ---------------------------------	
	FILE *fout = fopen("c++_mpz", "wb");

	
	if(fout != NULL) {
		mpz_out_raw(fout, a.get_mpz_t());
		mpz_out_raw(fout, b.get_mpz_t());
		mpz_out_raw(fout, c.get_mpz_t());
		fclose(fout);
	} else {
		cout << "No output file." << endl;
		exit(1);
	}
	
	mpz_t buff;	// basic mpz_t
	mpz_init_set_si(buff,0);
	FILE *fin  = fopen("c++_mpz", "rb");	
	if(fin != NULL){
		mpz_inp_raw(buff,fin);
		c = mpz_class(buff);	// convert mpz_t to mpz_class
		mpz_inp_raw(buff,fin);
		a = mpz_class(buff);
		mpz_inp_raw(buff,fin);
		b = mpz_class(buff);
	} else {
		cout << "No input file." << endl;
		exit(2);
	}	
		
	cout << "file read" << endl;
	cout << "c:" << c << endl;
	cout << "a:" << a << endl;
	cout << "b:" << b << endl;
		
  return 0;
}

