/****************************************************************************************
*  BigIntegerClient.c
*  Test client for BigInteger ADT
*****************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "BigInteger.h"

int main(int argc, char* argv[])
{
	char *str = "-0041085449"; //
	char *str2= "6402779357";
	
	// char *str3 = "3";
	// char *str4 = "2";
	
	// char *str5 = "9";
	// char *str6 = "16";
	BigInteger A = stringToBigInteger(str);
	BigInteger B = stringToBigInteger(str2);
	
	// BigInteger out5,out6,out7,out8,out9;
	// BigInteger three = stringToBigInteger(str3);
	// BigInteger two = stringToBigInteger(str4);
	// BigInteger nine = stringToBigInteger(str5);
	// BigInteger sixteen = stringToBigInteger(str6);
	printf("A: ");
	printBigInteger(stdout, A);
	printf("B: ");
	printBigInteger(stdout, B);
	//printf("sign of A is %i, sign of B is %i\n", sign(A), sign(B));
	//𝐴, 𝐵, 𝐴 + 𝐵, 𝐴 − 𝐵, 𝐴 − 𝐴, 3𝐴 − 2𝐵, 𝐴𝐵, 𝐴2, 𝐵2, 9𝐴4 + 16𝐵5

	BigInteger S = stringToBigInteger(str);
	BigInteger S2 = stringToBigInteger(str);	
	BigInteger S3 = stringToBigInteger(str);	
	BigInteger S4 = stringToBigInteger(str);	
	BigInteger S5 = stringToBigInteger(str);	
	BigInteger S6 = stringToBigInteger(str);	
	BigInteger S7 = stringToBigInteger(str);	
	BigInteger S8 = stringToBigInteger(str);	
	BigInteger S9 = stringToBigInteger(str);	
	BigInteger S10 = stringToBigInteger(str);	

	S = sum(A,B);
	printf("sign of A+A is %i\nA+B is ", sign(S));
	printBigInteger(stdout, S);
	
	subtract(S,A,B);
	printf("sign of A-B is %i\nA-B is ", sign(S));
	printBigInteger(stdout, S);
	
	subtract(S,A,A);
	printf("sign of A-A is %i\nA-B is ", sign(S));
	printBigInteger(stdout, S);
	
    char* num = "3";
	BigInteger num1 = stringToBigInteger(num);
   
	multiply(S2,A,num1);
	printf("3A: ");
	printBigInteger(stdout, S2);
	
	num = "2";
	BigInteger num2 = stringToBigInteger(num);
   
	multiply(S3,B,num2);
	printf("2B: ");
	printBigInteger(stdout, S3);
	
	subtract(S4,S2,S3);
	printf("3A-2B: ");
	printBigInteger(stdout, S4);
	
	multiply(S5,A,B);
	printf("AB: ");
	printBigInteger(stdout, S5);
	//-263061064730276293
	
	multiply(S6,A,A);
	printf("A^2: ");
	printBigInteger(stdout, S6);
	
	multiply(S7,B,B);
	printf("A^2: ");
	printBigInteger(stdout, S7);
	//40995583494425333449
	
	num = "9";
	BigInteger num3 = stringToBigInteger(num);
   
	multiply(S8,A,A);
	printBigInteger(stdout, S8);
	multiply(S8,S8,A);
	printBigInteger(stdout, S8);
	multiply(S8,S8,A);
	printBigInteger(stdout, S8);
	multiply(S8,S8,num3);
	printf("9A4: ");
	printBigInteger(stdout, S8);
	
	num = "16";
	BigInteger num4 = stringToBigInteger(num);
   
	multiply(S9,B,B);
	
	printBigInteger(stdout, S9);
	multiply(S9,S9,B);
	multiply(S9,S9,B);
	multiply(S9,S9,B);
	multiply(S9,S9,num4);
	printf("16B5: ");
	printBigInteger(stdout, S9);
	
	add(S10,S8,S9);
	printf("9A+16B: ");
	printBigInteger(stdout, S10);
	//172172054965235507489029369166881131954970903225721
	return 0;
}