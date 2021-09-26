//-----------------------------------------------------------------------------
// Alan Szeto
// 1672580
// pa2
// Arithmetic.c
// I/O file for BigInteger ADT
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "BigInteger.h"
#define NUM 300
#include<stdio.h>
#include<stdlib.h>
#include"BigInteger.h"
     
int main(int argc, char * argv[]){

   int size;
   FILE *in, *out;

   // checks the command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // opens read and write files
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   //scan the in file
   fscanf(in, "%i", &size);
   char* str1 = malloc(size+1);
   fscanf(in, "%s", str1);
   fscanf(in, "%i", &size);
   char* str2 = malloc(size+1);
   fscanf(in, "%s", str2);
   BigInteger A = stringToBigInteger(str1);
   BigInteger B = stringToBigInteger(str2);
   
   //stores calculations
   BigInteger S,S2,S3,S4,S5,S6,S7,S8;
   BigInteger D,D2,D3,D4,D5,D6;
   BigInteger E,E2,E3,F1,F2,G;
   printBigInteger(out,A);
   printBigInteger(out,B);
   
   //A+B
   S = sum(A,B);
   printBigInteger(out,S);
   
   //A-B
   S2 = diff(A,B);
   printBigInteger(out,S2);
   
   //A-A
   S3 = diff(A,A);
   printBigInteger(out,S3);
   
   //3A-2B
   char* num = "3";
   D = stringToBigInteger(num);
   E = prod(D,A);
   num = "2";
   D2 = stringToBigInteger(num);
   F1 = prod(D2,B);
   S4 = diff(E,F1);
   printBigInteger(out,S4);
   
   //AB
   S5 = prod(A,B);
   printBigInteger(out,S5);
   
   //A^2
   D3 = copy(A);
   S6 = prod(A,D3);
   printBigInteger(out,S6);
   
   //B^2
   D4 = copy(B);
   S7 = prod(B,D4);
   printBigInteger(out,S7);
   
   //A"9A^4 - 16B^5
   num = "9";
   D5 = stringToBigInteger(num);
   E2 = copy(A);
   for(int i = 0; i < 3; i++){
	   E2 = prod(E2,A);
   }
   F2 = prod(D5,E2);
   //makeZero(D5);
   num = "16";
   D6 = stringToBigInteger(num);
   E3 = copy(B);
   for(int i = 0; i < 4; i++){
	   E3 = prod(E3,B);
   }
   G = prod(D6,E3);
   //makeZero(D);
   S8 = sum(F2,G);
   printBigInteger(out,S8);

   
   //close infiles
   fclose(in);
   fclose(out);
   
   str1 = NULL;
   str2 = NULL;
   free(str1);
   free(str2);
   freeBigInteger(&(A)); freeBigInteger(&(B));
   freeBigInteger(&(S)); freeBigInteger(&(S2));
   freeBigInteger(&(S3)); freeBigInteger(&(S4));
   freeBigInteger(&(S5)); freeBigInteger(&(S6));
   freeBigInteger(&(S7)); freeBigInteger((&S8));
   freeBigInteger(&(D)); freeBigInteger(&(D2));
   freeBigInteger(&(D3)); freeBigInteger(&(D4));
   freeBigInteger(&(D5)); freeBigInteger(&(D6));
   freeBigInteger(&(E)); freeBigInteger(&(E2));
   freeBigInteger(&(E3)); freeBigInteger(&(F1));
   freeBigInteger(&(F2)); freeBigInteger(&(G));
   return(0);
}