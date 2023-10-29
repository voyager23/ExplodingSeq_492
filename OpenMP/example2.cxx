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

int main (int argc, char *argv[]) {

  int th_id, nthreads;
  
  
#pragma omp parallel private(th_id)

  //th_id is declared above.  It is is specified as private; so each
  //thread will have its own copy of th_id
  {
    th_id = omp_get_thread_num();
    std::cout << "Hello World from thread " << th_id << std::endl;
  }

}
