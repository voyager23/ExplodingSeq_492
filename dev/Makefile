# makefile for dev folder

mod_chk : mod_chk.cxx
	g++ -std=c++17 mod_chk.cxx -o ../bin/modchk 

via : rw_via_c.cxx
	g++ rw_via_c.cxx -lgmp -l gmpxx -o ../bin/rw_via
	
crw : c_rw_mpz_t.c
	gcc c_rw_mpz_t.c -lgmp -o ../bin/c_rw_mpz_t
	
rw : rw_mpz_t.cxx
	g++ rw_mpz_t.cxx -lgmp -lgmpxx -o ../bin/rw_mpz_t
	
limit : limit.cxx
	g++ -std=c++17 limit.cxx -o ../bin/limit 

run :
	../bin/modchk
	
