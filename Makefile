SRC=bool.cc
EXE=bool

all: $(SRC)
	g++ -O2 -std=c++0x $(SRC) -o $(EXE)

clean:
	rm -rf $(EXE)
