#include <vector>
#include <iostream>
using namespace std;

class Sudoku {
  public:
    Sudoku();
    void Print_Screen();
    int Solve();
  protected:
    int Is_Row_Valid(int r);
    int Is_Col_Valid(int c);
    int Is_Panel_Valid(int sr, int sc);
    int Recursive_Solve(int r, int c);
    vector <string> Grid;
    vector <int> checker;
};
