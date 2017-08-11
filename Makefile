SRC=bool.cc
EXE=bool
CXXFLAG=-O2 -std=c++0x -Wall -pedantic
CXXLIBRARY=-lreadline

all: $(SRC)
	g++ $(CXXFLAG) $(CXXLIBRARY) $(SRC) -o $(EXE)

clean:
	rm -rf $(EXE)

.PHONY: clean
