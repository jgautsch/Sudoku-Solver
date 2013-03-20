# Sudoku Solver. Solves any 9x9 Solvable Sudoku Puzzle

## HOW THE USER USES THE PROGRAM:
	
###	The program is built by running make in the program directory. 

The user uses the program by running it by either passing the filename to the program as an argument
like './main filename.txt'.  If the user does not pass the filename to the program as an argument, then the user 
will be prompted to enter the filename while in the program.  Then the sudoku will be solved and the solution 
will be printed to the screen.

If the user wants to visualize how the computer is solving the puzzle, there are 3 lines I put in the 
recursiveSolve() function in the Puzzle.cpp file that can be uncommented that will clear the console, print the
board, and usleep(7000). This will print the board in the same spot in its current state on every pass of the 
recursiveSolve, so you see exactly what the computer is working on/thinking or moving towards the solution.
**Warning: Don't do this for hard puzzles, because it will take forever.**



## HOW THE PROGRAM WORKS INTERNALLY:

The program works internally by using the Puzzle class.  The main functionality of the program uses
the Puzzle class's constructors and functions printBoard(), solve(), recursiveSolve(), and the functions that 
check if rows, columns and mini grids are valid - isRowValid(), isColValid(), and isMiniGridValid(). 

Once the constructor sets the 2D vector Board to the represent the puzzle passed to the program and
verifies that it is a valid puzzle, the board is printed to show the user the puzzle, and then the solve() function
is called. The solve function simply calls the recursiveSolve() function, which solves the puzzle by checking
if potential values lead to a solution. Values that are not a potential solution are not tried (leaving the entire
branches of those values alone, because they're a waste of time).  If there is only one possible value for a given
space, it is filled in and the puzzle moves on.  If there's multiple possible values for a spot, it tests them to
see if they lead to a solution.  Each time a possible value is entered in a spot, the recursiveSolve() function
checks the row and column and mini grid to ensure that it is a valid play, if it's not, it doesn't go any farther 
down that branch, because it doesn't lead to a solution.  If it does, it keeps recursing and calls recursiveSolve
with the new hypothetical step to a solution. 
	



## HOW THE PROGRAM WAS VERIFIED:

During the course of running the program, each move on the board is verified by the row, column
and mini grid validator functions in the program to make sure repeats aren't tolerated.  Then once the program
was successfully and consistently outputting solutions, they were checked by using my program to solve 
sudoku puzzles, and then plugging those puzzles into other solvers (online) and comparing the solutions.
The solutions were the same so my program solves them correctly. 




## WHAT WORKED/DIDN'T WORK WELL, AND GENERALLY "HOW" IT WAS IMPLEMENTED:

Reading in of the puzzle by default reads from a file using the file io stream. The file can be 
passed to the program as an argument when running the program, or by typing in the filename while running
the program. The file is then opened, and read into a vector of strings, each row as a string. The vector
of strings is then converted to the integer tokens and pushed into the 2D vector of vector<int> Board, and
then the program is ready to cook. This all happens in the non-default constructor that takes the file name
as a string. The puzzle can also be read in using the istream and the default constructor, which reads in the
puzzle ints from the istream and constructs the Board using those. Using it this way involves changing the 
main.cpp program however. If the user changed the main.cpp file to just use the default constructor, the puzzle
would be passed to the istream of the program at execution time by doing something like this: './main < puzzle.txt'.

The checking of rows, columns, and mini grids involves using the vector<int> checker.  When each 
of the checker/validating functions is called, the are checking a particular row, column, or mini grid.  First the
checker vector is filled with zeros. Then the row/col/minigrid is iterated through and the index corresponding
to the value in each row/col/minigrid cell is changed in the checker vector from 0 to 1, to indicate that that
value exists in the row/col/minigrid.  If the function finds a value twice in the row/col/minigrid, then it will
realize that that index in the checker vector is already 1, and so it is a repeat value and will return 0 because
it is an invalid row/col/minigrid that won't work.
	
#	NOW, the real meat of the program- the solving.
	
I had first tried some kind of ridiculous and slow (we're talking like O(n^3 or 4) mega iteration loop set
that would iterate over the row and cols and mini grids filling in values when they were obvious, and then 
taking a fresh look at the puzzle to see if that newly filled in spot revealed any more obvious to solve spots, and 
running that until (hopefully) all the spots were filled in. This only worked for very easy puzzles I tested it with,
and wouldn't work for anything that didn't have a chain of clearly obvious spot fill-ins leading to the solution.

I had to scrap that because it didn't work, and so read about solving recursively.  Sudoku can be thought
of as a giant tree, with each node being a potential board state, and branches reach out to a board state that
has all the same numbers, plus one more spot filled in. In this tree of potential board values, there are lots and lots 
of invalid boards and branches. An invalid branch starts with a single invalid board. The unsolved problem is 
the root node, and assuming it has a unique solution, has one leaf node that is the solution.  The recursiveSolve
algorithm places potential values in the empty slots, not placing invalid values (because they lead to invalid 
branches, and not the solution) and checking validity at every number placement to check if it leads to an
invalid branch.  If placing that value leads to an invalid branch, or doesn't lead to a solution, that branch is ignored, and
the recursion returns back up to the value placement that sent it to an invalid branch. This applies recursively, which 
is hard to explain in words, but if an arbitrary branch only leads to invalid branches, the program finds that out
and jumps back to that value that made the branch that only lead to the invalid branches, and tries something else
because that value doesn't lead to a solution, so isn't the right value.  When run, this will not go all the way down all
the invalid branches because it identifies them recursively, and only reaches all the way down to the solution leaf. Once
the solution is found (it is valid on all accounts, and row and col are both at the end) recursiveSolve returns 1
all the way up its cool recursive chain to signal that it found the solution, and to keep it.  The solution is then printed.
This recursion is awesome.




