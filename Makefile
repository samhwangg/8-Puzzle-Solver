all: main.cpp eightPuzzle.o
	g++ main.cpp eightPuzzle.o

eightPuzzle: eightPuzzle.cpp eightPuzzle.h
	g++ -c eightPuzzle.cpp -o eightPuzzle.o


