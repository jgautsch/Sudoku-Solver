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


/***************************************************/
// Puzzle() Constructor:
//  - This is the 
/***************************************************/

Puzzle::Puzzle() {

  int c; // Placeholder for the ints we read in from the file.

  // These resizings prevent my seg fault.
  //
  Board.resize(9); 
  checker.resize(9+1);

  // Loop through the size the board ought to be, reading in from the file
  for ( int i = 0; i < 9; i++ ) {
    for ( int j = 0; j < 9; j++ ) {

      // Attempt to read in the file elements,
      // and put what we read into c
      if (!(cin >> c)) {
        cout << "Problem reading file" << endl;
        exit(1);
      } 

      // Push the c value we read in into our v2int Board
      if (c == 0 || (c > 0 && c <= 9)) {  
        Board[i].push_back(c);
      } else {

        // Encountered a bad file element, that doesn't make sense
        cout << "Bad file element. This doesn't look like the examples." << endl;
        exit(1);
      } 
    }
  }
  
  // Now that we've read it in, make sure it has valid rows, columns
  // and minigrids. 

  // Loop through the indexes of the rows and cols we want to check, checking each
  for ( int i = 0; i < 9; i++ ) {

    // First checking the row at i index
    if (!isRowValid(i)) {
      
      cout << "Invalid row" << endl;
      exit(1);
    }

    // Then checking the column at i index
    if (!isColValid(i)) {
      
      cout << "Invalid column" << endl;
      exit(1);
    }
  }
  
  // Now we're going to check the minigrids. All 9 of them.
  // Loop through the locations of the minigrids, and check them.
  for ( int i = 0; i < 9; i += 3 ) {
    for ( int j = 0; j < 9; j += 3 ) {
      if (!isMiniGridValid(i, j)) {
        
        cout << "Invalid mini grid" << endl;
        exit(1);
      }
    }
  }
}


/***************************************************/
// Puzzle( string ) Constructor:
//
/***************************************************/

Puzzle::Puzzle( string filename ) {
    
  // Read in line by line from the file
  // into the vec_of_int puzzle
  ifstream myfile;
  myfile.open( filename.c_str() );
  
  // Make sure the file is open before doing this stuff
  if ( !myfile.is_open() ) {
      cout << "Error opening the file" << endl;
      cout << "What's weird is that this works in the command line." << endl;
      return;
  }
  
  
  /// THIS IS FOR TESTING
  string line;
  
  while ( getline( myfile, line ) ) {
      test.push_back( line );
  }
  
  myfile.close();
  
  // NOW TEST THAT IT WORKED BY PRINTING IT OUT
  //print();

  // These resizings prevent my seg fault.
  //
  Board.resize(9); 
  checker.resize(9+1);

  int c;

  for (int i = 0; i < test.size(); ++i) {

    string s = test[i];
    istringstream iss(s);

    for (int j = 0; j < 9; ++j) {

      if (!(iss >> c)) {
        cout << "Problem reading file" << endl;
        exit(1);
      }

      // Push the c value we read in into our v2int Board
      if (c == 0 || (c > 0 && c <= 9)) {  
        Board[i].push_back(c);
      } else {

        // Encountered a bad file element, that doesn't make sense
        cout << "Bad file element. This doesn't look like the examples." << endl;
        exit(1);
      } 
    } 
  }

  
  // Now that we've read it in, make sure it has valid rows, columns
  // and minigrids. 

  // Loop through the indexes of the rows and cols we want to check, checking each
  for ( int i = 0; i < 9; i++ ) {

    // First checking the row at i index
    if (!isRowValid(i)) {
      
      cout << "Invalid row" << endl;
      exit(1);
    }

    // Then checking the column at i index
    if (!isColValid(i)) {
      
      cout << "Invalid column" << endl;
      exit(1);
    }
  }
  
  // Now we're going to check the minigrids. All 9 of them.
  // Loop through the locations of the minigrids, and check them.
  for ( int i = 0; i < 9; i += 3 ) {
    for ( int j = 0; j < 9; j += 3 ) {
      if (!isMiniGridValid(i, j)) {
        
        cout << "Invalid mini grid" << endl;
        exit(1);
      }
    }
  }
}


/***************************************************/
// printBoard() Function:
//
/***************************************************/

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


/***************************************************/
// solve() Function:
//
/***************************************************/

int Puzzle::solve() {

  return recursiveSolve(0, 0);
}


/***************************************************/
// isRowValid() Function:
//
/***************************************************/

int Puzzle::isRowValid(int row) {

  for ( int i = 0; i <= 9; i++ ) checker[i] = 0;

  for ( int i = 0; i < 9; i++ ) {
    if (Board[row][i] != 0) {
      if (checker[Board[row][i]]) return 0;
      checker[Board[row][i]] = 1;
    }
  }
  return 1;
}


/***************************************************/
// isColValid() Function:
//
/***************************************************/

int Puzzle::isColValid(int col) {
    
  for ( int i = 0; i <= 9; i++ ) checker[i] = 0;

  for ( int i = 0; i < 9; i++ ) {
    if (Board[i][col] != 0) {
      if (checker[Board[i][col]]) return 0;
      checker[Board[i][col]] = 1;
    }
  }
  return 1;
}


/***************************************************/
// isMiniGridValid() Function:
//
/***************************************************/

int Puzzle::isMiniGridValid(int mgRow, int mgCol) {

  int row, col;
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


/***************************************************/
// recursiveSolve() Function:
//
/***************************************************/

int Puzzle::recursiveSolve(int row, int col) {
  
  // Skip all non-dash characters 
  while ( row < 9 && Board[row][col] != 0 ) {
    col++;
    if (col == 9) {
      row++;
      col = 0;
    }
  }

  // Base case -- if row == 9, we're done so we can stop recursing
  if (row == 9) return 1;

  // Try each value.  If successful, then return true. 
  for ( int i = 1; i <= 9; i++ ) {
    Board[row][col] = i;
    if (isRowValid(row) && 
        isColValid(col) && 
        isMiniGridValid(row-row%3, col-col%3) &&
        recursiveSolve(row, col)) {
      return 1;
    }
  }

  // If unsuccessful, reset the element and return false.
  
  Board[row][col] = 0;
  return 0;
}

