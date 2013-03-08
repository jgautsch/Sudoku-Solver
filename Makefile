all: main

main: main.o sudoku.o
	g++ main.o sudoku.o -o main

sudoku.o: sudoku.cpp
	g++ -c sudoku.cpp

clean:
	rm -f *.o main
