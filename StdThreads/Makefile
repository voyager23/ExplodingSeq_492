#Makefile for StdThreads folder

bnt : bNoThreads.cxx
	g++ -std=c++17 bNoThreads.cxx -g -o ./bnt
	
bt : bThreads.cxx
	g++ -std=c++17 bThreads.cxx -g -o ./bt
	
# Phoney
db : ./bnt
	gdb ./bnt
	
