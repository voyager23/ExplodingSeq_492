/*
 * checkMillerRabin.cxx
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
#include <set>
#include <cstdint>
#include "../inc/MillerRabin.hxx"
using namespace std;

int main(int argc, char **argv)
{
	set<uint32_t> primes ={1000000007,1000000009,1000000021,1000000033,
		1000000087,1000000093,1000000097,1000000103,1000000123,1000000181,
		1000000207,1000000223,1000000241,1000000271,1000000289,1000000297,1000000321,1000000349,1000000363,1000000403,
		1000000409,1000000411,1000000427,1000000433,1000000439,1000000447,1000000453,1000000459,1000000483,1000000513,
		1000000531,1000000579,1000000607,1000000613,1000000637,1000000663,1000000711,1000000753,1000000787,1000000801,
		1000000829,1000000861,1000000871,1000000891,1000000901,1000000919,1000000931,1000000933,1000000993,1000001011};
		
		// For a known prime, if MR reports false this is a missed prime.
		for(auto i = primes.begin(); i != primes.end(); ++i) {
			bool r = MillerRabin(*i);
			if(r == false) cout << "Missed " << *i << endl;
		}
	return 0;
}

