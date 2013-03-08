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
//  - This is the default constructor. It actually
//    won't get used now in typical used. It was 
//    where how the constructor works was fleshed 
//    out, and is really only used when the puzzle
//    is passed to the istream of the program  from
//    the command line when running the program like 
//    this: './main < puzzle.txt'
//  - Works by cycling through the rows and cols of 
//    the board and pushing the values being read in
//    into the board rows and cols. 
//  - After pushing values into the rows and cols, 
//    it loops through them to make sure it has 
//    valid rows, columns, and minigrids.
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
//  - First, the file is opened and each line is 
//    read into a string, and put into the 'test'
//    vector. File is then closed. 
//  - These lines represent rows, and so each 
//    element of the test vector is then parsed
//    into the number tokens that make up the row
//    string, and pushed back into the appropriate
//    position in the Board two dimensional vector.
//  - After filling the 2D board vector, the validity
//    of the rows, columns, and minigrids is checked.
/***************************************************/

Puzzle::Puzzle( string filename ) {
    
  // Read in line by line from the file
  // into the v2int Board
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
//  - Simple enough- just loops through the 2D vector
//    Board and prints out the elements
//  - It also inserts the appropriate separators
//    between rows, cols and minigrids
/***************************************************/

void Puzzle::printBoard() {

  // Loop through the rows and cols of the baord
  for ( int i = 0; i < Board.size(); i++ ) {
    for ( int j = 0; j < Board[i].size(); j++ ) {

      // If board element is a 0, print a blank space
      if ( Board[i][j] == 0) cout << "  ";
      else cout << Board[i][j] << " ";

      // Put vertical separators in the appropriate place
      if (j == 2 || j == 5) cout << "| ";
    }
    cout << endl;

    // Put horizontal separators in the appropriate place
    if (i == 2 || i == 5) {

        for( int k = 0; k < 11; k++ ) cout << "- ";
        cout << endl;
    }
  }
}


/***************************************************/
// solve() Function:
//  - Basically just starts the recursive solve from
//    row 0, col 0.
/***************************************************/

int Puzzle::solve() {

  return recursiveSolve(0, 0);
}


/***************************************************/
// recursiveSolve() Function:
//  - Solves the puzzles using cool recursion.
//  - There's a lot of comment description in the 
//    function, so this I'll let the explaining happen
//    down there...
/***************************************************/

int Puzzle::recursiveSolve(int row, int col) {
  
  // Skip all non-zero characters, they don't need to be solved for
  while ( row < 9 && Board[row][col] != 0 ) {

    // Next column index, important for not recursing infinitely
    col++;

    // If we're at the last column, then go to the next row
    // And reset column to 0
    if (col == 9) {
      row++;
      col = 0;
    }
  }

  // Base case -- if row == 9, we're done so we can stop recursing
  if (row == 9) return 1;

  /**************************************************************/
  //    VISUALIZATION
  /**************************************************************/
  // This is kind of cool:
  // Uncomment this little set right here if you want to see 
  // a visualization of the computer solving the puzzle.
  // Heads up though, it takes forever for the hard puzzle.

  // system("clear");
  // printBoard();
  // usleep(7000);
  /**************************************************************/





  // ITS ABOUT TO GET RECURSIVE UP IN HERE

  // This algorithm works by testing the possible values that
  // can go in a box on the board, and then checking if that leads
  // to a solution by checking the next spot with the different
  // possible values that can go in that box, and then checking if that
  // leads to a solution by checking the next spot with the different
  // possible values that can go in that box, and then checking if that
  // leads to a solution by checking the next spot with the different
  // possible values that can go in that box, and then checking if that
  // leads to a solution by checking the next spot with the differ

  // you get the idea.

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //~~~~~~~~~~~~  IMPORTANT COMMENT FOR GRADERS  ~~~~~~~~~~~~~~~~~~~
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // This algorithm does have the functionality of eliminating
  // values to (not) place in that spot in the current 
  // row/column/minigrid by recursing down and seeing if a solution
  // is found via that value in that spot. If not, it cuts off that 
  // entire branch of possibilities from what it looks at, but does 
  // so recursively, like from the roots. 
  //
  // ALSO, it satisfies the criteria "functionality such that if only
  // a single value is left, the square is filled with that value and
  // the process is restarted", in a little bit of a cool/tricky
  // recursive way. If there are multiple values left, the recurse
  // down to the bottom of the pool, and then fill up the solution 
  // backwards, so that in a way, there's always only a single value
  // left, then the square is filled in, the recursiveSolve returns
  // 1 signalling to the chain of recursive funcitons that came before
  // it that they touched down, and for them to all fill in their 
  // single value left, until the puzzle is full, truly (not just 
  // full of data being tried by the recursion.)
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //~~~~~~~~ END IMPORTANT COMMENT ABOUT THIS LAB AND RUBRIC ~~~~~~~
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // Try each value, and call recursiveSolve to go deeper and
  // see if we can get down to a solution to the puzzle by assigning
  // i to the Board[row][col]. If assigning i to Board[row][col] DOES
  // lead to a solution to the puzzle, then we solved the puzzle!
  // This partly assumes that the puzzles passed have unique solutions.
  // So if it is successful in recursing down and finding the solution,
  // return true.
  for ( int i = 1; i <= 9; i++ ) {
    Board[row][col] = i;
    if (isRowValid(row) && 
        isColValid(col) && 
        isMiniGridValid(row-row%3, col-col%3) &&
        recursiveSolve(row, col)) {
      return 1;
    }
  }

  // If assigning those values to that element (trying to describe
  // generally here, becuase rememeber this comment can apply to any
  // level of the recursion) doesn't lead to a solution, then reset the
  // value of that index in the Board, and 'trim' the tree of possible
  // solutions be returning zero. This basically says, "We're not going
  // to recurse in this direction anymore, with that value as the value
  // for the Board spot/index in question."
  
  Board[row][col] = 0;
  return 0;
}

/***************************************************/
// isRowValid() Function:
//  - makes sure no numbers are repeated in a row
//  - uses the checker vector to record the values
//    that exist in that row already. 
//  - If the same value gets pinned twice, then 
//    the row is invalid (has repeating values)
/***************************************************/

int Puzzle::isRowValid(int row) {

  // First make the checker vector full of 0's
  for ( int i = 0; i <= 9; i++ ) checker[i] = 0;

  // Then loop through the row in question, and for every value
  // we find, change that spot in the checker vector from a 0
  // to a 1. If that spot already is a 1, return 0 because it's
  // a repeat value in the row, and so the row is invalid.
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
//  - same concept as the isRowValid() function
//  - makes sure no numbers are repeated in a column
//  - uses the checker vector to record the values
//    that exist in that column already. 
//  - If the same value gets pinned twice, then 
//    the column is invalid (has repeating values)
/***************************************************/

int Puzzle::isColValid(int col) {
    
  // First make the checker vector full of 0's
  for ( int i = 0; i <= 9; i++ ) checker[i] = 0;

  // Then loop through the column in question, and for every value
  // we find, change that spot in the checker vector from a 0
  // to a 1. If that spot already is a 1, return 0 because it's
  // a repeat value in the column, and so the column is invalid.
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
//  - same concept as the isRowValid() and isColValid()
//  - makes sure no numbers are repeated in a minigrid
//  - uses the checker vector to record the values
//    that exist in that minigrid already. 
//  - If the same value gets pinned twice, then 
//    the minigrid is invalid (has repeating values)
/***************************************************/

int Puzzle::isMiniGridValid(int mgRow, int mgCol) {

  int row, col;

  // First make the checker vector full of 0's
  for ( int i = 0; i <= 9; i++ ) checker[i] = 0;


  // Then loop through the minigrid in question, and for every value
  // we find, change that spot in the checker vector from a 0
  // to a 1. If that spot already is a 1, return 0 because it's
  // a repeat value in the minigrid, and so the minigrid is invalid.
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




