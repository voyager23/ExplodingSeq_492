/*
 * example1.cxx
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
#include <omp.h>

//example4.c: add all elements in an array in parallel  



int main() {

  const int N=100; 
  int a[N]; 

  //initialize 
  for (int i=0; i < N; i++)
    a[i] = i; 

  //compute sum 
  int local_sum, sum; 
#pragma omp parallel private(local_sum) shared(sum) 
  { 
    local_sum =0; 
    
    //the array is distributed statically between threads
#pragma omp for schedule(static,1) 
    for (int i=0; i< N; i++) {
      local_sum += a[i]; 
    }

    //each thread calculated its local_sum. ALl threads have to add to
    //the global sum. It is critical that this operation is atomic.

#pragma omp critical 
    sum += local_sum;
  } 


  printf("sum=%d should be %d\n", sum, N*(N-1)/2);
}


