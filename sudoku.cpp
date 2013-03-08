#include <cstdio>
#include <cstdlib>
#include "sudoku.h"

Sudoku::Sudoku()
{
  int i, j;
  char c;

  cout << "!!!!       " << Grid.size() << endl;
  Grid.resize(9);
  checker.resize('9'+1);

  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (!(cin >> c)) {
        cerr << "Bad Sudoku File -- not enough entries\n";
        exit(1);
      } 
      if (c == '-' || (c >= '0' && c <= '9')) {
        Grid[i].push_back(c);
      } else {
        cerr << "Bad Sudoku File -- entry: " << c << endl;
        exit(1);
      } 
    }
  }
  for (i = 0; i < 9; i++) {
    if (!isRowValid(i)) {
      cerr << "Bad Sudoku File -- Bad row " << i << endl;
      exit(1);
    }
    if (!isColValid(i)) {
      cerr << "Bad Sudoku File -- Bad col " << i << endl;
      exit(1);
    }
  }
  for (i = 0; i < 9; i += 3) {
    for (j = 0; j < 9; j += 3) {
      if (!isMiniGridValid(i, j)) {
        cerr << "Bad Sudoku File -- Bad panel starting at row " << i << " col " << j << endl;
        exit(1);
      }
    }
  }
}

void Sudoku::printBoard()
{
  int i, j;

  for (i = 0; i < Grid.size(); i++) {
    for (j = 0; j < Grid[i].size(); j++) {
      //if (j != 0) printf(" ");
      printf("%c ", Grid[i][j]);
      if (j == 2 || j == 5) printf("| ");
    }
    printf("\n");
    if (i == 2 || i == 5) {
        for( int k = 0; k < 11; k++) cout << "- ";
        cout << endl;
    }
  }
}

int Sudoku::solve()
{
  return recursiveSolve(0, 0);
}

int Sudoku::isRowValid(int r)
{
  int i;

  for (i = '0'; i <= '9'; i++) checker[i] = 0;

  for (i = 0; i < 9; i++) {
    if (Grid[r][i] != '-') {
      if (checker[Grid[r][i]]) return 0;
      checker[Grid[r][i]] = 1;
    }
  }
  return 1;
}

int Sudoku::isColValid(int c)
{
  int i, j;
    
  for (i = '0'; i <= '9'; i++) checker[i] = 0;

  for (i = 0; i < 9; i++) {
    if (Grid[i][c] != '-') {
      if (checker[Grid[i][c]]) return 0;
      checker[Grid[i][c]] = 1;
    }
  }
  return 1;
}

int Sudoku::isMiniGridValid(int sr, int sc)
{
  int r, c, i;
  for (i = '0'; i <= '9'; i++) checker[i] = 0;

  for (r = sr; r < sr+3; r++) {
    for (c = sc; c < sc+3; c++) {
      if (Grid[r][c] != '-') {
        if (checker[Grid[r][c]]) return 0;
        checker[Grid[r][c]] = 1;
      }
    }
  }
  return 1;
}

int Sudoku::recursiveSolve(int r, int c)
{
  int i;
  
  /* Skip all non-dash characters */
  while (r < 9 && Grid[r][c] != '-') {
    c++;
    if (c == 9) {
      r++;
      c = 0;
    }
  }

  /* Base case -- we're done */
  if (r == 9) return 1;

  /* Try each value.  If successful, then return true. */
  for (i = '1'; i <= '9'; i++) {
    Grid[r][c] = i;
    if (isRowValid(r) && 
        isColValid(c) && 
        isMiniGridValid(r-r%3, c-c%3) &&
        recursiveSolve(r, c)) {
      return 1;
    }
  }

  /* If unsuccessful, reset the element and return false. */
  
  Grid[r][c] = '-';
  return 0;
}

