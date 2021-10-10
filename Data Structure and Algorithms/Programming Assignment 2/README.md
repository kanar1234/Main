Matrix.c:
Creates functions to change matrices (uses linked list from Programming Assignment 1)

//Matrix Functions

  newMatrix(int n) - creates a new matrix of size n (n is the row of the Matrix and an empty linked list is the column)

  newEntry(int n, double d) - creates a new entry object containing column = n and value = d //not used

  freeMatrix() - frees matrix

  size(Matrix M) - returns size of matrix M

  NNZ(Matrix M) - returns number of non-zero elements in matrix M

  equals(Matrix A, Matrix B) - returns true if A = B else returns false

  makeZero(Matrix M) - remove all columns of the matrix M

  changeEntry(Matrix M, int i, int j, double x) - sets Matrix[i][j] to x

  copy(Matrix A) - returns a copy of matrix A

  transpose(Matrix A) - returns the transpose of matrix A

  scalarMult(double x, Matrix A) - returns the matrix A scaled by x

  sumMatrix(Matrix A, Matrix B) - returns the sum of matrix A and B

  diff(Matrix A, Matrix B) - returns the difference of matrix A and B

  vectorDot(List L1, List L2) - returns the vector dot product of two lists

  product(Matrix A, Matrix B) - returns the product of matrix A and B

  printMatrix(Matrix M) - prints the matrix onto the terminal

List.c:
Creates a doubly linked list and List ADT

List.h:
Has the List functions

Sparse.c:
Takes in input from files and tests its functions

Makefile:
Given - Compiles Matrix List and Matrix Test
