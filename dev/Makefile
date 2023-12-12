# makefile for dev folder

EXE=../bin/csnip

csnip : c_snip.cxx
	g++ -std=c++17 -g c_snip.cxx -o $(EXE)
	
bsnip : b_snip.cxx
	g++ -std=c++17 -g b_snip.cxx -o ../bin/bsnip

bdev : b_dev.cxx
	g++ -std=c++17 -g b_dev.cxx -o ../bin/bdev
	
#........................................

adev : a_dev.cxx
	g++ -std=c++17 -g a_dev.cxx -o $(EXE)
	
mod_chk : mod_chk.cxx
	g++ -std=c++17 -g mod_chk.cxx -o $(EXE)
	 
csm : checkSimpleMap.cxx
	g++ -std=c++17 -g checkSimpleMap.cxx -o ../bin/csm
	
iter : iterator.cxx
	g++ -std=c++17 -g iterator.cxx -o $(EXE) 

via : rw_via_c.cxx
	g++ rw_via_c.cxx -lgmp -l gmpxx -o ../bin/rw_via
	
crw : c_rw_mpz_t.c
	gcc c_rw_mpz_t.c -lgmp -o ../bin/c_rw_mpz_t
	
rw : rw_mpz_t.cxx
	g++ rw_mpz_t.cxx -lgmp -lgmpxx -o ../bin/rw_mpz_t
	
limit : limit.cxx
	g++ -std=c++17 limit.cxx -o ../bin/limit 
#--------------------------------------
db :
	gdb $(EXE)
run :
	$(EXE)
#--------------------------------------
	
