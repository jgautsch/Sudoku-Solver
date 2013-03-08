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


/***************************************************/
// printAndSolve() Function:
//  - Basically just for not repeating the control
//    and flow of the program.
//  - It calls a coupld of comands on the Puzzle
//    instance, and prints a few things too.
/***************************************************/

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


/***************************************************/
// main() Function:
//  - Where it all begins. 
/***************************************************/

int main(int argc, char *argv[]) {

  // Welcome the user to the program
  cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << "Welcome to Jon's Sudoku solver." << endl;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n" << endl;

  // If the user passed the puzzle file as an argument, run with it.
  if (argv[1]) {

    // Call Puzzle constructor passing it the name of the file
    Puzzle sudoku( argv[1] );

    // Now go through the print and solve steps/commands
    printAndSolve( sudoku );

  // Else if the didn't pass the program a puzzle to solve, ask them for 
  // a puzzle filename
  } else {
    string filename;
    cout << "No puzzle file was passed to the program as an argument." << endl;
    cout << "Please enter the filename of the puzzle you wish to solve." << endl;
    cout << ">> ";
    cin >> filename;

    // Call Puzzle constructor passing it the name of the file
    Puzzle sudoku( filename );

    // Now go through the print and solve steps/commands
    printAndSolve( sudoku );

  }
  
  return 0;
}
