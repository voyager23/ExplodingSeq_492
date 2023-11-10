#Makefile for StdThreads folder
	
ct : cThreads.cxx
	g++ -std=c++17 cThreads.cxx -o ./ct
	
bnt : bNoThreads.cxx
	g++ -std=c++17 bNoThreads.cxx -g -o ./bnt
	
bt : bThreads.cxx
	g++ -std=c++17 bThreads.cxx -g -o ./bt
	
# Phoney
db : ./bnt
	gdb ./bnt
	
