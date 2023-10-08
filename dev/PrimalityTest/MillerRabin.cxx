/*
 * MillerRabin.c
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
 
#include "./MillerRabin.hxx"

using namespace std;

int main(int argc, char **argv)
{
	const u64 p_hi = 1000000000;	// 10^9
	const u64 p_lo = 10000000;		// 10^7
	u64 count = 0;
	for(u64 n = p_hi+1; n < p_hi+p_lo; n+=2){
		if (MillerRabin(n)) {
			cout << n << " is prime." << endl;
			count += 1;
			if(count > 10) exit(0);
		}
	}
	cout << "Found " << count << " primes between " << p_hi << " and " << p_hi+p_lo << endl;
	return 0;
}

