#include <vector>
#include <iostream>
using namespace std;

class Sudoku {
  public:
    Sudoku();
    void printBoard();
    int solve();
  protected:
    int isRowValid(int r);
    int isColValid(int c);
    int isMiniGridValid(int sr, int sc);
    int recursiveSolve(int r, int c);
    vector <string> Grid;
    vector <int> checker;
};
