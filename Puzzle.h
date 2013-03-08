//
//  Puzzle.h
//  lab6
//
//  Created by Jon Gautsch on 2/28/13.
//  Copyright (c) 2013 Jon Gautsch. All rights reserved.
//

#ifndef __lab6__Puzzle__
#define __lab6__Puzzle__

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

typedef vector<int> VecOfInt;
typedef vector<VecOfInt> v2int;

class Puzzle {

  public:

    Puzzle();           // Default constuctor. Was made for passing puzzle file to istream
    Puzzle( string );   // Constructor that takes file name
    void printBoard();  // Prints the puzzle board
    int solve();        // The solve function. Really just starts the recursive solve
    
  private:

    int isRowValid(int row);                    // Checks to insure the rows are valid
    int isColValid(int col);                    // Checks to ensure the columns are valid
    int isMiniGridValid(int mgRow, int mgCol);  // Checks to ensure the minigrids are valid
    int recursiveSolve(int row, int col);       // Recursive solving algorithm

    v2int Board;            // The puzzle board
    VecOfInt checker;       // A checker vector used in checking validity of rows etc...
    vector<string> test;    // A vector for holding a string. Used when reading in the file.
};


#endif /* defined(__lab6__Puzzle__) */
