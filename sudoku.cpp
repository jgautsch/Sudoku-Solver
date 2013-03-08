#include <cstdio>
#include <cstdlib>
#include "sudoku.h"

Sudoku::Sudoku() {

  int i, j;
  char c;

  cout << "!!!!       " << Grid.size() << endl;
  Grid.resize(9);
  checker.resize('9'+1);

  for ( int i = 0; i < 9; i++ ) {
    for ( int j = 0; j < 9; j++ ) {

      // Attempt to read in the file elements
      if (!(cin >> c)) {
        cout << "Problem reading file" << endl;
        exit(1);
      } 

      // Read in the file elements
      if (c == '-' || (c >= '0' && c <= '9')) {
        Grid[i].push_back(c);
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

void Sudoku::printBoard() {

  for ( int i = 0; i < Grid.size(); i++ ) {
    for ( int j = 0; j < Grid[i].size(); j++ ) {

      if ( Grid[i][j] == '-') cout << "  ";
      else cout << Grid[i][j] << " ";

      if (j == 2 || j == 5) printf("| ");
    }
    cout << endl;

    if (i == 2 || i == 5) {

        for( int k = 0; k < 11; k++ ) cout << "- ";
        cout << endl;
    }
  }
}

int Sudoku::solve() {

  return recursiveSolve(0, 0);
}

int Sudoku::isRowValid(int row) {

  int i;

  for ( int i = '0'; i <= '9'; i++ ) checker[i] = 0;

  for ( int i = 0; i < 9; i++ ) {
    if (Grid[row][i] != '-') {
      if (checker[Grid[row][i]]) return 0;
      checker[Grid[row][i]] = 1;
    }
  }
  return 1;
}

int Sudoku::isColValid(int col) {

  int i, j;
    
  for ( int i = '0'; i <= '9'; i++ ) checker[i] = 0;

  for ( int i = 0; i < 9; i++ ) {
    if (Grid[i][col] != '-') {
      if (checker[Grid[i][col]]) return 0;
      checker[Grid[i][col]] = 1;
    }
  }
  return 1;
}

int Sudoku::isMiniGridValid(int mgRow, int mgCol) {

  int row, col, i;
  for ( int i = '0'; i <= '9'; i++ ) checker[i] = 0;

  for ( row = mgRow; row < mgRow+3; row++ ) {
    for ( col = mgCol; col < mgCol+3; col++ ) {
      if (Grid[row][col] != '-') {
        if (checker[Grid[row][col]]) return 0;
        checker[Grid[row][col]] = 1;
      }
    }
  }
  return 1;
}

int Sudoku::recursiveSolve(int row, int col) {

  int i;
  
  /* Skip all non-dash characters */
  while ( row < 9 && Grid[row][col] != '-' ) {
    col++;
    if (col == 9) {
      row++;
      col = 0;
    }
  }

  /* Base case -- we're done */
  if (row == 9) return 1;

  /* Try each value.  If successful, then return true. */
  for ( int i = '1'; i <= '9'; i++ ) {
    Grid[row][col] = i;
    if (isRowValid(row) && 
        isColValid(col) && 
        isMiniGridValid(row-row%3, col-col%3) &&
        recursiveSolve(row, col)) {
      return 1;
    }
  }

  /* If unsuccessful, reset the element and return false. */
  
  Grid[row][col] = '-';
  return 0;
}

