/*
 * c_rw_mpz_t.c
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


#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int main(int argc, char **argv)
{
	mpz_t a,b,c;
	mpz_init_set_si(a, +1177L);
	mpz_init_set_si(b, -2152L);
	mpz_init_set_si(c, +987654321L);
	
	gmp_printf ("%s is an mpz %Zd\n", "a", a);
	gmp_printf ("%s is an mpz %Zd\n", "b", b);
	gmp_printf ("%s is an mpz %Zd\n", "c", c);
	
	FILE *fout = fopen("mpz_abc", "wb");
	if(fout != NULL) {
		mpz_out_raw(fout, a);
		mpz_out_raw(fout, b);
		mpz_out_raw(fout, c);
	}
	fclose(fout);
	
	mpz_set_si(a,0L);
	mpz_set_si(b,0L);
	mpz_set_si(c,0L);
	
	gmp_printf ("%s is an mpz %Zd\n", "a", a);
	gmp_printf ("%s is an mpz %Zd\n", "b", b);
	gmp_printf ("%s is an mpz %Zd\n", "c", c);
	
	FILE *fin = fopen("mpz_abc", "rb");
	if(fin != NULL) {
		mpz_inp_raw(a,fin);
		mpz_inp_raw(b,fin);
		mpz_inp_raw(c,fin);
	}
	fclose(fin);
	
	gmp_printf ("%s is an mpz %Zd\n", "c", c);
	gmp_printf ("%s is an mpz %Zd\n", "a", a);
	gmp_printf ("%s is an mpz %Zd\n", "b", b);
		
	return 0;
}

