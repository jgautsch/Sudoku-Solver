#include <vector>
#include <iostream>
using namespace std;

class Puzzle {
  public:
    Puzzle();
    void printBoard();
    int solve();
  protected:
    int isRowValid(int row);
    int isColValid(int col);
    int isMiniGridValid(int mgRow, int mgCol);
    int recursiveSolve(int row, int col);
    vector <string> Grid;
    vector <int> checker;
};
