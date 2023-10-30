# Makefile for OpenMP folder

dp : d_primes.cxx
	g++ -fopenmp d_primes.cxx -g -o ./dp
	
cp : c_primes.cxx
	g++ -fopenmp c_primes.cxx -g -o ./cp

bp : b_primes.cxx
	g++ -fopenmp b_primes.cxx -g -o ./bp
	
px1 : primes_example.cxx
	g++ -fopenmp primes_example.cxx -o ./px1

run :
	$(EXE)
	
db :
	gdb $(EXE)
