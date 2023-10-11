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
#include <vector>
#include <map>
using u64 = uint64_t;
using u128 = __uint128_t;
using namespace std;

u64 cycle_length(u64 modulus) {
	map<u64,u64> sequence;
	sequence.emplace(1,1);	// std::pair<a[index], index>
	u64 index = 1;
	u64 a = 1;
	while(1){
		a = (6*a*a + 10*a + 3) % modulus;
		index += 1;
		auto r = se quence.emplace(a,index); // r is pair<iterator,bool>
		if(r.second) continue; // emplace succeded
		// match found
		// using the result iterator extract a pair<a[a[index], index>
		// cycle length is difference of indexes	
		cout << index << " " << std::get<1>((*(std::get<0>(r)))) << " " << endl;
		return (u64)(index - std::get<1>((*(std::get<0>(r)))));
		break;
	}
	return 0;
}

u64 calc_a_n_mod_p(u64 modulus, u64 n){
	// find the cycle length
	map<u64,u64> sequence;
	sequence.emplace(1,1);	// std::pair<a[index], index>
	u64 index = 1;
	u64 a = 1;
	while(1){
		a = (6*a*a + 10*a + 3) % modulus;
		index += 1;
		auto r = sequence.emplace(a,index); // r is pair<iterator,bool>
		if(r.second) continue; // emplace succeded
		// match found
		// using the result iterator extract a pair<a[a[index], index>
		// cycle length is difference of indexes	
		cout << index << " " << std::get<1>((*(std::get<0>(r)))) << " " << endl;
		u64 cycle_length = (index - std::get<1>((*(std::get<0>(r)))));
		u64 idx = n % cycle_length;
		cout << "a[n] = " << sequence[idx-1] << endl;
		break;
	}
	return 0;	// error return
}







int main(int argc, char **argv)
{
	//~ vector<u64> moduli = {1000000007,1000000009,1000000021,1000000033,
		//~ 1000000087,1000000093,1000000097,1000000103,1000000123,
		//~ 1000000181,1000000207};
		
	calc_a_n_mod_p(997,1000);
	
	const u64 mod = 997;	
	vector<u64> moduli = {mod};
	vector<u64> results = {};
	for(u64 &mod : moduli) {
		u64 a = 1;
		results.push_back(a);
		for(unsigned n = 2; n != 1001; ++n) {
			a = ((6*a*a) + (10*a) + 3) % mod;
			results.push_back(a);
		}
		cout << "a[1000]: mod " << mod << " = " << a << endl;
		u64 index = 1;
		for(u64 &r : results){
			cout << index << ": " << r << endl;
			index += 1;
		}

	}
	u64 c_length = cycle_length(mod);
	cout << 1000 % c_length << endl;
	return 0;
}

