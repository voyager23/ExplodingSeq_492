/*
 * primes_example.cxx
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
#include <vector>
#include <omp.h>
#include "../inc/MillerRabin.hxx"

using u64 = uint64_t;
using u32 = uint32_t;
using namespace std;

// Definitions
vector<u64>prime_modulus(u64 x, u64 y){
	// approx 25 seconds for x=10^9 and y=10^7 returns 482449 values
	vector<u64> primes = {};
	if((x % 2)==0) x += 1; // test odd values
	for(u64 p = x; p <= x+y; p+=2) {
		if (MillerRabin(p)) {
				primes.push_back(p);
		}
	}
	return primes;
}

int main(int argc, char **argv)
{
	vector<u64> primes = prime_modulus(1e4, 2e3);
	cout << "vector size: " << primes.size() << endl;
	u64 Sum = 0;
	for(auto &p : primes) Sum += p;
	cout << "Sum of vector: " << Sum << endl;
	
  //compute sum 
  u64 local_sum, B = 0; 
#pragma omp parallel private(local_sum) shared(B) 
  { 
    local_sum =0; 
    
    //the array is distributed statically between threads
#pragma omp for schedule(static,8) 
    for (int i=0; i< primes.size(); i++) {
      local_sum += primes[i]; 
    }

    //each thread calculated its local_sum. ALl threads have to add to
    //the global sum. It is critical that this operation is atomic.

#pragma omp critical 
    B += local_sum;
  } 

	cout << "B = " << B << endl;
	return 0;
}

