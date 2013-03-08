#include <cstdio>
#include <cstdlib>
#include "sudoku.h"

void usage(string s)
{
  cerr << "usage: sudoku solve(yes|no) output-type(screen|convert) - puzzle on stdin\n";
  if (s != "") cerr << s << endl;
  exit(0);
}
  
int main(int argc, char *argv[]) {
  
  Sudoku puzzle;
    
  cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << "Welcome to Jon's Sudoku solver." << endl;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << "\nThe given puzzle looks like this: \n\n";

  puzzle.printBoard();

  if (!puzzle.solve()) {
    printf("Cannot solve puzzle\n");
    exit(0);
  }
    
  cout << "\n\nThe solved puzzle looks like this: \n\n";

  puzzle.printBoard();
  cout << "\n\n";

  return 0;
}
