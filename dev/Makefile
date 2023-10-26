# makefile for dev folder

EXE=../bin/iter

csm : checkSimpleMap.cxx
	g++ -std=c++17 -g checkSimpleMap.cxx -o ../bin/csm
	
iter : iterator.cxx
	g++ -std=c++17 -g iterator.cxx -o $(EXE) 

mod_chk : mod_chk.cxx
	g++ -std=c++17 -g mod_chk.cxx -o $(EXE) 

via : rw_via_c.cxx
	g++ rw_via_c.cxx -lgmp -l gmpxx -o ../bin/rw_via
	
crw : c_rw_mpz_t.c
	gcc c_rw_mpz_t.c -lgmp -o ../bin/c_rw_mpz_t
	
rw : rw_mpz_t.cxx
	g++ rw_mpz_t.cxx -lgmp -lgmpxx -o ../bin/rw_mpz_t
	
limit : limit.cxx
	g++ -std=c++17 limit.cxx -o ../bin/limit 

run :
	$(EXE)
	
