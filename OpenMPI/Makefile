# Makefile for OpenMP folder

TARGET=new_search

$(TARGET): $(TARGET).cxx
	# Compile
	mpic++ -std=c++17 -Wall -Wno-unused-variable -g -fpermissive new_search.cxx -o ./$(TARGET)
	# Syncronize
	./sync_wdir.sh

nusrch : new_search.cxx
	g++ -std=c++17 -g new_search.cxx -o ./nusrch

.PHONY: run db

run :
	$(EXE)
	
db :
	gdb $(EXE)

TARGET=ddev

.PHONY: run

