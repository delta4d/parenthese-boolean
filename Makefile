SRC=bool.cc
EXE=bool

all: $(SRC)
	g++ -O2 -std=c++0x -Wall -pedantic $(SRC) -o $(EXE)

clean:
	rm -rf $(EXE)
