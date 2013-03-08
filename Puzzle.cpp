//
//  Puzzle.cpp
//  lab6_part1
//
//  Created by Jon Gautsch on 2/28/13.
//  Copyright (c) 2013 Jon Gautsch. All rights reserved.
//

#include <cstdio>
#include <cstdlib>
#include "Puzzle.h"

Puzzle::Puzzle() {

  int i, j;
  int c;

  Board.resize(9); // This, it turns out, prevents my seg fault.

  checker.resize(9+1);

  for ( int i = 0; i < 9; i++ ) {
    for ( int j = 0; j < 9; j++ ) {

      // Attempt to read in the file elements
      if (!(cin >> c)) {
        cout << "Problem reading file" << endl;
        exit(1);
      } 

      // Read in the file elements
      //if (c == '-' || (c >= '0' && c <= '9')) {
      if (c == 0 || (c > 0 && c <= 9)) {  
        Board[i].push_back(c);
      } else {

        // Encountered a bad file element, that doesn't make sense
        cout << "Bad file element. This doesn't look like the examples." << endl;
        exit(1);
      } 
    }
  }
  
  for ( int i = 0; i < 9; i++ ) {
    if (!isRowValid(i)) {
      
      cout << "Invalid row" << endl;
      exit(1);
    }
    if (!isColValid(i)) {
      
      cout << "Invalid column" << endl;
      exit(1);
    }
  }
  
  for ( int i = 0; i < 9; i += 3 ) {
    for ( int j = 0; j < 9; j += 3 ) {
      if (!isMiniGridValid(i, j)) {
        
        cout << "Invalid mini grid" << endl;
        exit(1);
      }
    }
  }
}

void Puzzle::printBoard() {

  for ( int i = 0; i < Board.size(); i++ ) {
    for ( int j = 0; j < Board[i].size(); j++ ) {

      if ( Board[i][j] == 0) cout << "  ";
      else cout << Board[i][j] << " ";

      if (j == 2 || j == 5) cout << "| ";
    }
    cout << endl;

    if (i == 2 || i == 5) {

        for( int k = 0; k < 11; k++ ) cout << "- ";
        cout << endl;
    }
  }
}

int Puzzle::solve() {

  return recursiveSolve(0, 0);
}

int Puzzle::isRowValid(int row) {

  int i;

  for ( int i = 0; i <= 9; i++ ) checker[i] = 0;

  for ( int i = 0; i < 9; i++ ) {
    if (Board[row][i] != 0) {
      if (checker[Board[row][i]]) return 0;
      checker[Board[row][i]] = 1;
    }
  }
  return 1;
}

int Puzzle::isColValid(int col) {

  int i, j;
    
  for ( int i = 0; i <= 9; i++ ) checker[i] = 0;

  for ( int i = 0; i < 9; i++ ) {
    if (Board[i][col] != 0) {
      if (checker[Board[i][col]]) return 0;
      checker[Board[i][col]] = 1;
    }
  }
  return 1;
}

int Puzzle::isMiniGridValid(int mgRow, int mgCol) {

  int row, col, i;
  for ( int i = 0; i <= 9; i++ ) checker[i] = 0;

  for ( row = mgRow; row < mgRow+3; row++ ) {
    for ( col = mgCol; col < mgCol+3; col++ ) {
      if (Board[row][col] != 0) {
        if (checker[Board[row][col]]) return 0;
        checker[Board[row][col]] = 1;
      }
    }
  }
  return 1;
}

int Puzzle::recursiveSolve(int row, int col) {

  int i;
  
  /* Skip all non-dash characters */
  while ( row < 9 && Board[row][col] != 0 ) {
    col++;
    if (col == 9) {
      row++;
      col = 0;
    }
  }

  /* Base case -- we're done */
  if (row == 9) return 1;

  /* Try each value.  If successful, then return true. */
  for ( int i = 1; i <= 9; i++ ) {
    Board[row][col] = i;
    if (isRowValid(row) && 
        isColValid(col) && 
        isMiniGridValid(row-row%3, col-col%3) &&
        recursiveSolve(row, col)) {
      return 1;
    }
  }

  /* If unsuccessful, reset the element and return false. */
  
  Board[row][col] = 0;
  return 0;
}

