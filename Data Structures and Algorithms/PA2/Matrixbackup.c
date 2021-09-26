#include<stdio.h>
#include<stdlib.h>
#include "Matrix.h"
#include "List.c"
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct EntryObj{
   int column;
   double value;
} EntryObj;

// private Node type
typedef EntryObj* Entry;

// private ListObj type
typedef struct MatrixObj{
	int size;
	List* rows;
} MatrixObj;

//private Matrix type
typedef MatrixObj* Matrix;
// Constructors-Destructors ---------------------------------------------------


// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n)
{
	Matrix M = malloc(sizeof(MatrixObj));
	M->rows = calloc(n+1, sizeof(ListObj));
	for(int i = 0; i < n; i++)
	{
		M->rows[i] = newList();
	}
	M->size = n;
	return M;
}

//newEntry()
//
Entry newEntry(int n, double d)
{
	Entry E = malloc(sizeof(EntryObj));
	E->column = n;
	E->value = d;
	return(E);
}

//freeEntry()

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM)
{
	if(pM != NULL && *pM != NULL && (*pM)->size>0)
	{
		int i = 0;
		List pL = (*pM)->rows[i];
		for(int i; i < (*pM)->size; i++)
		{
			freeList(&pL);
		}
	}
	free(*pM);
	*pM = NULL;
}

// Access Functions ---------------------------------------------------

// size()
// Return the size of square Matrix M.
int size(Matrix M)
{
	if( M==NULL )
	{
      printf("Matrix Error: calling size() on NULL List reference\n");
      exit(1);
    }
	return(M->size);
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M)
{
	int count = 0;
	for(int i = 0; i < M->size; i++)
	{
		count += M->rows[i]->length;
	}
	return count;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B)
{
   int eq = 0;
   List L = NULL;
   List L2 = NULL;
   Node N = NULL;
   Node N2 = NULL;

   if( A==NULL || B==NULL )
   {
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }

   eq = ( A->size == B->size );

   for(int i = 0; i < A->size; i++)
   {
	    L = A->rows[i];
		L2 = B->rows[i];
		N = L->front;
		N2 = L2->front;
		while( eq && (N != NULL || N2 != NULL))
		{
			if(N == NULL)
			{
				if(N2 == NULL)
				{
					eq = 1;
				}
				else
				{
					eq = 0;
				}
			}
			else if(N2 == NULL)
			{
				eq = 0;
			}
			else
			{
				eq = (N->data == N2->data);
				N = N->next;
				N2 = N2->next;
			}
		}
   }
   return eq;
}


// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix.
void makeZero(Matrix M)
{
	if( M == NULL)
	{
    printf("List Error: calling makeZero() on NULL Matrix reference\n");
    exit(1);
	}
	for(int i = 0; i < M->size; i++)
	{
		clear(M->rows[i]);
	}
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x)
{
	if( i > M->size || i <1 || j > M->size || j < 1)
	{
		printf("List Error: calling changeEntry() on NULL or Out of Bound Matrix reference\n");
		exit(1);
	}
	List L = M->rows[i-1];
	int prev, k = 0;
	moveFront(L);
	//checks if column is less than j or if the list is empty
	if(L->cursor == NULL)
	{
		if(x != 0)
		{
			prepend(L,newEntry(j,x));
			k++;
		}
		else
		{
			k++;
		}
	}
	//else checks if prev < column < j 
	//if column == j
	//or column > j
	while (k != 1)
	{
		Entry E = L->cursor->data;
		prev = E->column;
		if(E->column == j)
		{
			if(x == 0)
			{
				delete(L);
				k++;
			}
			else
			{
				E->value = x;
				k++;
			}
		}
		if(L->cursor->next == NULL && k != 1)
		{
			if(x != 0)
			{
				append(L,newEntry(j,x));
				k++;
			}
			else
			{
				k++;
			}
		}
		else
		{
			moveNext(L);
		}
		if (E->column > j && j > prev)
		{
			if(x != 0)
			{
				insertBefore(L, newEntry(j,x));
				k++;
			}
			else
			{
				k++;
			}
		}
	}
}
// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A)
{
	Node N = NULL;
	Entry E = NULL;
	List L = NULL;
	if(A->size < 0)
	{
		printf("List Error: calling copy() on NULL Matrix reference\n");
		exit(1);
	}
	Matrix M = newMatrix(A->size);	
	for(int i = 0; i < A->size; i++)
	{
		L = A->rows[i];
		for(N = L->front; N != NULL; N = N->next)
		{	
			E = N->data;
			append(M->rows[i], E);
		}
	}
	return M;
}
// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A)
{
	if(A->size < 0)
	{
		printf("List Error: calling transpose() on NULL Matrix reference\n");
		exit(1);
	}
	Matrix M = newMatrix(A->size);
	Entry E = NULL;
	List L = NULL;
	Node N = NULL;
	for(int i = 0; i < A->size; i++)
	{
		L = A->rows[i];
		for(N = L->front; N != NULL; N = N->next)
		{
			E = N->data;
			changeEntry(M,E->column,i+1,E->value);			
		}
	}
	return M;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A)
{
	Node N = NULL;
	Entry E = NULL;
	List L = NULL;
	if(A->size < 0)
	{
		printf("List Error: calling copy() on NULL Matrix reference\n");
		exit(1);
	}
	Matrix M = newMatrix(A->size);	
	for(int i = 0; i < A->size; i++)
	{
		L = A->rows[i];
		for(N = L->front; N != NULL; N = N->next)
		{	
			E = N->data; 
			Entry E2 = newEntry(E->column,E->value * x);
			append(M->rows[i], E2);
		}
	}
	return M;
}
// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B)
{
	if(A->size != B->size)
	{
		printf("List Error: calling sum() on bad Matrix reference\n");
		exit(1);
	}
	Matrix M = newMatrix(A->size);
	List L = NULL;
	List L2 = NULL;
	Node N = NULL;
	Node N2 = NULL;
	Entry E = NULL;
	Entry E2 = NULL;
	for(int i = 0; i < A->size; i++)
	{
		L = A->rows[i];
		L2 = B->rows[i];
		N = L->front;
		N2 = L2->front;
		while(N != NULL || N2 != NULL)
		{
			if(N == NULL)
			{
				E2 = N2->data;
				changeEntry(M,i+1,E2->column, E2->value);
				N2 = N2->next;
			}
			else if(N2 == NULL)
			{
				E = N->data;
				changeEntry(M,i+1,E->column, E->value);
				N = N->next;
			}
			else
			{
				E = N->data;
				E2 = N2->data;
				if(E->column == E2->column)
				{
					changeEntry(M, i+1, E->column,E->value + E2->value);
					N = N->next;
					N2 = N2->next;
				}
				else if(E->column > E2->column)
				{
					changeEntry(M,i+1,E2->column, E2->value);
					N2 = N2->next;
				}
				else
				{
					changeEntry(M,i+1,E->column, E->value);
					N = N->next;
				}
			}
		}
	}
	return M;
}
// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B)
{
	if(A->size != B->size)
	{
		printf("List Error: calling sum() on bad Matrix reference\n");
		exit(1);
	}
	Matrix M = newMatrix(100);
	List L = NULL;
	List L2 = NULL;
	Node N = NULL;
	Node N2 = NULL;
	Entry E = NULL;
	Entry E2 = NULL;
	for(int i = 0; i < A->size; i++)
	{
		L = A->rows[i];
		L2 = B->rows[i];
		N = L->front;
		N2 = L2->front;
		while(N != NULL || N2 != NULL)
		{
			//entry of NULL does not exist
			//so this statement sets existing 
			//entries to E and/or E2
			if(N == NULL)
			{
				E2 = N2->data;
			}
			else if(N2 == NULL)
			{
				E = N->data;
			}
			else
			{
				E = N->data;
				E2 = N2->data;
			}
			
			if(N == NULL)
			{
				changeEntry(M,i+1,E2->column, E2->value * -1);
				N2 = N2->next;
			}
			else if(N2 == NULL)
			{
				changeEntry(M,i+1,E->column, E->value);
				N = N->next;
			}
			else
			{
				if(E->column == E2->column)
				{
					changeEntry(M, i+1, E->column,E->value - E2->value);
					N = N->next;
					N2 = N2->next;
				}
				else if(E->column > E2->column)
				{
					changeEntry(M,i+1,E2->column, E2->value * -1);
					N2 = N2->next;
				}
				else
				{
					changeEntry(M,i+1,E->column, E->value);
					N = N->next;
				}
			}
		}
	}
	return M;
}

//function for product to find
//vector dot product of two lists
double vectorDot(List L, List L2)
{
	Node N = NULL;
	Node N2 = NULL;
	Entry E = NULL;
	Entry E2 = NULL;
	double i = 0;
	if(L->front == NULL || L2->front == NULL)
	{
		i = 0;
	}
	else
	{
		N = L->front;
		N2 = L2->front;
		while(N != NULL || N2 != NULL)
		{
			if(N == NULL || N2 == NULL)
			{
				N = NULL;
				N2 = NULL;
			}
			else
			{
				E = N->data;
				E2 = N2->data;
				if(E->column == E2->column)
				{
					i = i + E->value * E2->value;
					N = N->next;
					N2 = N2->next;
				}
				else if(E->column > E2->column)
				{
					N2 = N2->next;
				}
				else
				{
					N = N->next;
				}
			}
			
		}
	}
	return i;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B)
{
	Matrix B2 = transpose(B);
	if(A->size != B2->size)
	{
		printf("List Error: calling sum() on bad Matrix reference\n");
		exit(1);
	}
	Matrix M = newMatrix(A->size);
	List L = NULL;
	List L2 = NULL;
	Entry E = NULL;
	for(int i = 0; i < A->size; i++)
	{
		if(A->rows[i]->front != NULL)
		{
			L2 = B->rows[i];
			for(int j = 0; j <A->size; j++)
			{
				if(B2->rows[j]->front != NULL)
				{
					L = A->rows[j];
					E = newEntry(i+1,vectorDot(L,L2));
					if(E->value != 0)
					{
						append(M->rows[j], E);
					}
				}
			}
		}
	}	
	return M;
}
// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.*/
void printMatrix(Matrix M)
{
	Entry E = NULL;
	Node N = NULL;
	List L = NULL;
   if( M==NULL ){
      printf("Queue Error: calling printQueue() on NULL Queue reference\n");
      exit(1);
   }
	else{
		for(int i = 0; i < M->size; i++)
		{
			L = M->rows[i];
			if(L->front != NULL)
			{
				printf("%i:", i+1);
				for(N = L->front; N != NULL; N = N->next)
				{
					E = N->data;
					printf(" (%i %f)", E->column, E->value);
				}
			printf("\n");
			}
		}			
	}
}
