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
#include <gmp.h>
using namespace std;
int main(int argc, char **argv)
{
	mpz_t a = 1234;
	mpz_t b = -7766;
	mpz_t c = 987654321;
	FILE* myfile;
	myfile = fopen ("example.txt","wb");
	mpz_out_raw(myfile, a);
	myfile.fclose();

	return 0;
}

