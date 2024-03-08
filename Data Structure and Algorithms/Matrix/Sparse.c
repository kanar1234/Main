//-----------------------------------------------------------------------------
// Alan Szeto
// 1672580
// pa2
// Sparse.c
// Implementation file for Sparse ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"
#include<string.h>

int main(int argc, char * argv[])
{
	int n, a, b, row, column;
	double value;
	
	//opens input file from argv[1]
    FILE* in = fopen(argv[1], "r");
    //opens output file from argv[2]
    FILE* out = fopen(argv[2], "w");

	
	if(argc != 3)
	{
		printf("Error :( \n");
		exit(1);
	}

	fscanf(in,"%i",&n);
	fscanf(in,"%i",&a);
	fscanf(in,"%i",&b);
	
	Matrix A = newMatrix(n);
	Matrix B = newMatrix(n);
	Matrix C, D, E, F, G, H, I, J;
	
	//creates matrix A
 	for(int i = 0; i < a; i++)
	{
		fscanf(in,"%i",&row);
		fscanf(in,"%i",&column);
		fscanf(in,"%lf",&value);
		changeEntry(A, row, column, value);
	}
	
	//creates a matrix B
	for(int j = 0; j < b; j++)
	{
		fscanf(in,"%i",&row);
		fscanf(in,"%i",&column);
		fscanf(in,"%lf",&value);
		changeEntry(B, row, column, value);
	}
	
	printf("A has %d non-zero entries:\n", NNZ(A));
	printMatrix(out,A);
	printf("\n");

	printf("B has %d non-zero entries:\n", NNZ(B));
	printMatrix(out,B);
	printf("\n");

	C = scalarMult(1.5, A);
	printf("(1.5)*A = %d\n", NNZ(C));
	printMatrix(out,C);
	printf("\n");

	D = sum(A, B);
	printf("A + B = %d\n", NNZ(D));
	printMatrix(out,D);
	printf("\n");

	E = sum(A, A);
	printf("A + A = %d\n", NNZ(E));
	printMatrix(out,E);
	printf("\n");

	F = diff(B,A);
	printf("B - A = %d\n", NNZ(F));
	printMatrix(out,F);
	printf("\n");

	G = diff(A, A);
	printf("A - A = %d\n", NNZ(G));
	printMatrix(out,G);
	printf("\n");

	H = transpose(A);
	printf("Transpose(A) = %d\n", NNZ(H));
	printMatrix(out,H);
	printf("\n");
	
	I = product(A, B);
	printf("A * A = %d\n", NNZ(I));
	printMatrix(out,I);
	printf("\n");
	
	J = product(B, B);
	printf("B * B = %d\n", NNZ(J));
	printMatrix(out,J);
	printf("\n");



	//closes in and out files
	fclose(in);
	fclose(out);
	
	//Free memory
	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&C);
	freeMatrix(&D);
	freeMatrix(&E);
	freeMatrix(&F);
	freeMatrix(&G);
	freeMatrix(&H);
	
	return 0;
}
