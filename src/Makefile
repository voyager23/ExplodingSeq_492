# Makefile for source folder

EXE=../bin/bmk

bmk : bookmark.cxx
	g++ -std=c++17  bookmark.cxx -o $(EXE)
	
bsoln : b_soln.cxx
	g++ -std=c++17 -O2 b_soln.cxx -o $(EXE)
	
asoln : a_soln.cxx
	g++ -std=c++17 -O2 a_soln.cxx -o $(EXE)

mod_chk : mod_chk.cxx
	g++ -std=c++17 -g mod_chk.cxx -o $(EXE) 

run :
	$(EXE)
	
db :
	gdb $(EXE)
	
