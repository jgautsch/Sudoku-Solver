//
//  main.cpp
//  lab6
//
//  Created by Jon Gautsch on 2/28/13.
//  Copyright (c) 2013 Jon Gautsch. All rights reserved.
//

#include <cstdio>
#include <cstdlib>
#include "Puzzle.h"

void usage(string s)
{
  cerr << "usage: sudoku solve(yes|no) output-type(screen|convert) - puzzle on stdin\n";
  if (s != "") cerr << s << endl;
  exit(0);
}

void printAndSolve( Puzzle sudoku ) {

  cout << "\nThe given puzzle looks like this: \n\n";

  sudoku.printBoard();

  if (!sudoku.solve()) {
    printf("Cannot solve puzzle\n");
    exit(0);
  }
    
  cout << "\n\nThe solved puzzle looks like this: \n\n";

  sudoku.printBoard();
  cout << "\n\n";
}


void choiceOne( string filename ) {
  Puzzle sudoku( filename );
              
  printAndSolve( sudoku );
}

void choiceTwo() {
  Puzzle sudoku;

  printAndSolve( sudoku );

}

void choiceThree() {

  string filename;
  cout << "Enter the filename: " << endl;
  cout << ">> ";
  cin >> filename;
  Puzzle sudoku( filename );

  printAndSolve( sudoku );

}


int main(int argc, char *argv[]) {

  cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << "Welcome to Jon's Sudoku solver." << endl;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n" << endl;

  int choice;
  cout << "How is the file being handled? :" << endl;
  cout << "  (1) Passed as an argument to the program when running it?" << endl;
  cout << "       ex. './main puzzle.txt'" << endl;
  cout << "  (2) Passed into the in stream of the program executing?" << endl;
  cout << "       ex. './main < puzzle.txt'" << endl;
  cout << "  (3) Or would you like to type in the filename of the puzzle?" << endl;
  cout << ">> ";
  cin >> choice;

  do {
    switch( choice ) {

      case 1: choiceOne( argv[1] );
              break;

      case 2: choiceTwo();
              break;

      case 3: choiceThree();
              break;

      default: cout << "Invalid selection. Please choose again" << endl;
               cout << ">> ";
               cin >> choice;
               break;
    }
  } while( choice != 1 && choice != 2 && choice != 3 );
  
  return 0;
}
