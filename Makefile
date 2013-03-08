all: main

main: main.o Puzzle.o
	g++ main.o Puzzle.o -o main

Puzzle.o: Puzzle.cpp
	g++ -c Puzzle.cpp

clean:
	rm -f *.o main
