A multithreaded application in C with Pthreads - it determines whether the solution to a Sudoku puzzle is valid.

Identifying location and reason for an invalid puzzle
Any problematic cell in a puzzle causes at least one or more of the following three errors: value not between 1 and 9, duplicated value, and missing value.

When a row/column/subgrid thread identifies any error (so that the puzzle is not valid), the thread must print out the problematic row/column/puzzle location and the specific error to stdout (to be included in the screenshots).

For example, there are three error types,

puzzle[1][2] = 3, duplicated value

puzzle[4][5] = 10, not between 1 and 9

row[6], missing value 7

column[8], missing value 9
