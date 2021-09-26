//-----------------------------------------------------------------------------
// Alan Szeto
// 1672580
// pa2
// MatrixClient.c 
// A test client for the Matrix ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"
     
int main(){
   int n=100000;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   Matrix C, D, E, F, G, H;

   changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
   changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
   changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
   changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
   changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
   changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
   changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
   changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
   changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);

   printf("%d\n", NNZ(A));
   printMatrix(A);
   printf("\n");

   printf("%d\n", NNZ(B));
   printMatrix(B);
   printf("\n");

   C = scalarMult(1.5, A);
   printf("%d\n", NNZ(C));
   printMatrix(C);
   printf("\n");

   D = sum(A, B);
   printf("%d\n", NNZ(D));
   printMatrix(D);
   printf("\n");

   E = diff(A, A);
   printf("%d\n", NNZ(E));
   printMatrix(E);
   printf("\n");

   F = transpose(B);
   printf("%d\n", NNZ(F));
   printMatrix(F);
   printf("\n");

   G = product(B, B);
   printf("%d\n", NNZ(G));
   printMatrix(G);
   printf("\n");

   H = copy(A);
   printf("%d\n", NNZ(H));
   printMatrix(H);
   printf("\n");

   printf("%s\n", equals(A, H)?"true":"false" );
   printf("%s\n", equals(A, B)?"true":"false" );
   printf("%s\n", equals(A, A)?"true":"false" );

   makeZero(A);
   printf("%d\n", NNZ(A));
   printMatrix(A);

   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);

   return EXIT_SUCCESS;
}
