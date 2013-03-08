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
    Puzzle();
    Puzzle( string );
    void printBoard();
    int solve();
  private:
    int isRowValid(int row);
    int isColValid(int col);
    int isMiniGridValid(int mgRow, int mgCol);
    int recursiveSolve(int row, int col);
    v2int Board;
    VecOfInt checker;
    vector<string> test;
};


#endif /* defined(__lab6__Puzzle__) */
