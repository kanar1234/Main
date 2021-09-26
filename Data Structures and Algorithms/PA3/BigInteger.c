//-----------------------------------------------------------------------------
// Alan Szeto
// 1672580
// pa2
// BigInteger.c
// Implementation file for BigInteger ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <string.h>
#include "BigInteger.h"
#define power 3

// structs --------------------------------------------------------------------
const long base = pow(10, power);

// private BigIntegerObj type
typedef struct BigIntegerObj
{
	List list;
	int sign;
}BigIntegerObj;

// Constructors-Destructors ---------------------------------------------------
// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger()
{
	BigInteger B = malloc(sizeof(BigIntegerObj));
	B->list = newList();
	B->sign = 0;
	return B;
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN)
{
	if(pN != NULL && *pN != NULL)
	{
		List L = (*pN)->list;
		freeList(&L);
	}
	free(*pN);
	*pN = NULL;
}
// Access functions -----------------------------------------------------------
// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N)
{
	if(N == NULL)
	{
		printf("List Error: calling sign() on NULL List reference\n");
        exit(1);
	}
	if(N->sign > 0)
	{
		return 1;
	}
	else if(N->sign < 0)	
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B)
{
	if(A == NULL || B == NULL)
	{ 
		printf("List Error: calling compare() on NULL List reference\n");
        exit(1);
	}
	int comp = 0;
	//printf("Alength:%i\nBlength:%i\n",length(A->list),length(B->list));
	if(length(A->list) != length(B->list))
	{
		if(length(A->list) > length(B->list))
		{
			comp = 1;
		}
		else
		{
			comp = -1;
		}
	}
	else if(A->sign != B->sign)
	{
		if (A->sign > B->sign)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		moveFront(A->list);
		moveFront(B->list);
		while( comp == 0 && index(A->list) != -1)
		{
			
			//printf("A is:%i\nB is:%i\n",get(A->list),get(B->list));
			if(get(A->list) == get(B->list))
			{
				//printf("indexA is:%i\n",index(A->list));
				moveNext(A->list);
				moveNext(B->list);
				//printf("indexB is:%i\n",index(A->list));
			}
			else
			{
				if(get(A->list) > get(B->list))
					comp = 1;
				else
					comp = -1;
			}
		}
	}
	return comp;
}
// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B)
{
	if(A == NULL || B == NULL)
	{
		printf("List Error: calling equals() on NULL List reference\n");
		exit(1);
	}
	int eq = 1;
	if(length(A->list) != length(B->list))
	{
		eq = 0;
	}
	else if(A->sign != B->sign)
	{
		eq = 0;
	}
	else
	{
		moveFront(A->list);
		moveFront(B->list);
		while(eq && index(A->list) != -1)
		{
			eq = (get(A->list) == get(B->list));
			moveNext(A->list);
			moveNext(B->list);
		}
	}
	return eq;
}
// Manipulation procedures ----------------------------------------------------
// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N)
{
	clear(N->list);
	N->sign = 0;
	append(N->list,0);
}
// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N)
{
	if(N->sign == 1)
	{
		N->sign = -1;
	}
	else
	{
		if(N->sign == -1)
		{
			N->sign = 1;
		}
	}
}
// BigInteger Arithmetic operations -----------------------------------------------
// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s)
{
	if(strlen(s) < 1)
	{
		printf("List Error: calling stringToBigInteger() on empty string reference\n");
		exit(1);
	}
	for(int i = 0; i < strlen(s); i++)
	{
		if(s[i] > '9')
		{
			printf("List Error: string has characters\n");
			exit(1);
		}
	}
	BigInteger B = newBigInteger();
	if(s[0] == '-')
	{
		B->sign = -1;
	}
	else if(s[0] == '+')
	{
		B->sign = 1;
	}
	else
	{
		B->sign = 1;
	}	
	int offset = 0;
	//sets the start of the pointer after all the +,-, and 0's 
	while(s[offset] == '0' || s[offset] == '+' || s[offset] == '-') 
	{
		offset++;
	}
	int strLength = strlen(s) - offset; //-1 since im starting at 0
	int toLong = 0; //where string to long will be stored
	int baseL = 0; //offset for first node
	int counter = offset;
	char s2[power+1];
	for(int i = 0; i < (strLength+power-1)/power; i++)
	{
		if(i == 0 && strLength%power != 0)
		{
			baseL = strLength%power;
		}
		else
		{
			baseL = power;
		}
		for(int j = 0; j < baseL; j++)
		{
			s2[j] = s[counter];
			counter++;
		}
		// printf("s2 at %i is:", i);
		// printf(s2);
		// printf("\nloop is %i\n", (strLength+power-1)/power);
		toLong = atol(s2);
		//need to make s2 empty 
		for(int j = 0; j < baseL; j++)
		{
			s2[j] = '\0';
		}
		append(B->list, toLong);
	}
	return B;
}
// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N)
{
	if(N == NULL)
	{
		printf("List Error: calling copy() on NULL List reference\n");
		exit(1);
	}
	moveFront(N->list);
	BigInteger B = newBigInteger();
	for(int i = 0; i < length(N->list); i++)
	{
		append(B->list, get(N->list));
		moveNext(N->list);
	}
	B->sign = N->sign;
	return B;
}
// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B)
{
	if(A == NULL || B == NULL)
	{
		printf("List Error: calling add() on NULL List reference\n");
		exit(1);
	}
	
	int overflow = 0;
	clear(S->list);
	BigInteger Acopy = copy(A);
	BigInteger Bcopy = copy(B);
	//used when changing from add to subtract
	BigInteger Acopy2 = copy(A);
	BigInteger Bcopy2 = copy(B);
	
	moveBack(Acopy->list);
	moveBack(Bcopy->list);
	if(Acopy->sign == -1 || Bcopy->sign == -1)
	{
		//-A - B == -(A+B)
		if(A->sign == -1 && B->sign == -1)
		{
			Acopy2->sign = 1;
			Bcopy2->sign = 1;
			add(S,Acopy2,Bcopy2);
			S->sign = -1;
		}
		//-A+B sign depends on the larger value of A and B
		else if(A->sign == -1)
		{
			Acopy2->sign = 1;
			subtract(S,Bcopy,Acopy2);
		}
		//A-B sign depends on the larger of A and B
		else
		{
			Bcopy2->sign = 1;
			subtract(S,Acopy,Bcopy2);
		}
	}
	else
	{
		S->sign = 1;
		while(index(Acopy->list) != -1 || index(Bcopy->list) != -1)
		{
			if(index(Acopy->list) == -1)
				{
					prepend(S->list, get(Bcopy->list));
					movePrev(Bcopy->list);
					
	//printf("here!!!!!!!!!!!!!!!!\n");
	//printBigInteger(stdout,S);
				}
				else if(index(Bcopy->list) == -1)
				{
					prepend(S->list, get(Acopy->list));
					movePrev(Acopy->list);
					
	//printf("here2!!!!!!!!!!!!!!!!\n");
	//printBigInteger(stdout,S);
				}
				else
				{
					//printf("A is: %i\n",get(Acopy->list));
					//printf("B is: %i\n",get(Bcopy->list));
					prepend(S->list,get(Acopy->list) + get(Bcopy->list));
					
	//printf("A + B is: %i\n",get(Acopy->list) + get(Bcopy->list));
					movePrev(Acopy->list);
					movePrev(Bcopy->list);
					
	//printf("here3!!!!!!!!!!!!!!!!\n");
	//printBigInteger(stdout,S);
				}
		}
		
	}
	moveBack(S->list);
	for(int i = 0; i < length(S->list)-1; i++)
	{
		overflow = get(S->list)/base;
		set(S->list, get(S->list)%base);
		movePrev(S->list);
		set(S->list, get(S->list) + overflow); 
	}
	zeroCheck(S);
	//dealloc Acopy and Bcopy
	freeBigInteger(&(Acopy));
	freeBigInteger(&(Acopy2));
	freeBigInteger(&(Bcopy));
	freeBigInteger(&(Bcopy2));
}
// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B)
{
	BigInteger C = newBigInteger();
	add(C,A,B);
	return C;
}
// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
// note: if B > A, function performs subtract(B,A)
void subtract(BigInteger D, BigInteger A, BigInteger B)
{
	if(A == NULL || B == NULL)
	{
		printf("List Error: calling add() on NULL List reference\n");
		exit(1);
	}
	
	int underflow = 0;
	clear(D->list);
	BigInteger Acopy = copy(A);
	BigInteger Bcopy = copy(B);	
	BigInteger Acopy2 = copy(A);
	BigInteger Bcopy2 = copy(B);	
	moveBack(Acopy->list);
	moveBack(Bcopy->list);
	//(-A)-(B) = -(A+B)
	
	// printf("copy 1 is:");
	// printBigInteger(stdout,Acopy2);
	
	// printf("copy 2 is:");
	// printBigInteger(stdout,Bcopy2);
	
	if(A->sign == -1 && B->sign == 1)
	{
		// printf("Case 1\n");
		negate(Acopy2);
		printBigInteger(stdout,Acopy2);
		printBigInteger(stdout,Bcopy2);
		add(D,Acopy2,Bcopy);
		D->sign = -1;
	}
	//(A)-(-B) = (A+B) 
	else if(A->sign == 1 && B->sign == -1)
	{
		// printf("Case 2\n");
		negate(Bcopy2);
		add(D,Acopy,Bcopy2);
		D->sign = 1;
	}
	//(-A)-(-B) = -A+B = B-A 
	else if(A->sign == -1 && B->sign == -1)
	{
		// printf("Case 3\n");
		negate(Acopy2);
		negate(Bcopy2);
		D->sign = 1;
		subtract(D,Bcopy2,Acopy2);
	}
	//(A)-(B)
	else 
	{
		//printf("Main\n");
		D->sign = 1;
		while(index(Acopy->list) != -1 || index(Bcopy->list) != -1)
		{
			if(index(Acopy->list) == -1)
			{
				prepend(D->list, get(Bcopy->list) * -1);
				movePrev(Bcopy->list);
			}
			else if(index(Bcopy->list) == -1)
			{
				prepend(D->list, get(Acopy->list));
				movePrev(Acopy->list);
			}
			else
			{
				prepend(D->list,get(Acopy->list) - get(Bcopy->list));
				movePrev(Acopy->list);
				movePrev(Bcopy->list);
			}
		}
	}
	moveFront(D->list);
	{
		// printBigInteger(stdout,D);
		moveFront(D->list);
		if(get(D->list) < 0 && index(D->list) != 1)
		{
			//printf("Do i go here?????????\n");
			negate(D);
			for(int i = 0; i < length(D->list); i++)
			{
				set(D->list, get(D->list)*-1);
				moveNext(D->list);
			}
		}
		//printBigInteger(stdout,D);
	}
	zeroCheck(D);
	moveBack(D->list);
	//printf("index is:%i\n",index(D->list));
	if(index(D->list) != 0)
	{
		for(int i = 1; i < length(D->list); i++)
		{
			if(get(D->list) < 0)
			{
				underflow = 1;
				set(D->list, base + get(D->list));
			}
			else
			{
				underflow = 0;
			}
			movePrev(D->list);
			set(D->list, get(D->list) - underflow); 
		}
	}
	//printBigInteger(stdout,D);
	//free*******
	freeBigInteger(&(Acopy));
	freeBigInteger(&(Acopy2));
	freeBigInteger(&(Bcopy));
	freeBigInteger(&(Bcopy2));
}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B)
{
	BigInteger C = newBigInteger();
	subtract(C,A,B);
	return C;

}
// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B)
	{
	BigInteger Acopy = copy(A);
	BigInteger Bcopy = copy(B);
	//for adding 
	BigInteger X = newBigInteger();
	BigInteger Y = newBigInteger();
	clear(P->list);
	int overflow = 0;
	int counter = 0;
	moveBack(Acopy->list);
	moveBack(Bcopy->list);
	append(Y->list, 0);
	while(index(Bcopy->list) != -1)
		{
			prepend(X->list, get(Acopy->list)*get(Bcopy->list));
			movePrev(Acopy->list);
			if(index(Acopy->list) == -1)
			{
				movePrev(Bcopy->list);
				Y = sum(X,Y);
				clear(X->list);
				moveBack(Acopy->list);
				counter++;
				for(int i = 0; i < counter; i++)
				{
					prepend(X->list, 0);
				}
			}
		}
	moveBack(Y->list);
	for(int i = 0; i < length(Y->list)-1; i++)
	{
		overflow = get(Y->list)/base;
		set(Y->list, get(Y->list)%base);
		movePrev(Y->list);
		set(Y->list, get(Y->list) + overflow); 
	}
	moveFront(Y->list);
	int x = 0;
	int y = 0;
	//printf("Y is :%i\n",get(Y->list));
	while(get(Y->list) >= base)
	{
		x = get(Y->list)/base;
		y = get(Y->list)%base;
		//printf("x is :%i\ny is:%i\n",x,y);
		set(Y->list, y);
		prepend(Y->list, x);
		moveFront(Y->list);
	}
	P->list = copyList(Y->list);
	if(A->sign == B->sign*-1)
	{
		P->sign = -1;
	}
	else
	{
		P->sign = 1;
	}
	zeroCheck(P);
	freeBigInteger(&(Acopy));
	freeBigInteger(&(Bcopy));
	freeBigInteger(&(X));
	freeBigInteger(&(Y));
}
// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B)
{
	BigInteger C = newBigInteger();
	multiply(C,A,B);
	return C;
}
// Other operations -----------------------------------------------------------
// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* stdout, BigInteger N)
{
	if(length(N->list) == 0 )
	{
		printf("Length is too short\n");
	}
	
	if(N->sign == 0)
	{
		fprintf(stdout,"0");
	}
	else
	{	
		BigInteger P = newBigInteger();
		moveFront(N->list);
		if(N->sign == -1)
		{
			fprintf(stdout,"-");
		}
		while(index(N->list) != -1)
		{
			append(P->list, get(N->list));
			moveNext(N->list);
		}
		moveFront(P->list);
		while(index(P->list) != -1)
		{
			int n = get(P->list);
			int zeros = 0;
			if(get(P->list) == 0)
			{
				zeros++;
			}
			while (n != 0) 
			{
				n /= 10;
				++zeros;
			}
			zeros = power - zeros;
			if(index(P->list) != 0)
			{
				for(int i = 0; i < zeros; i++)
				{
					fprintf(stdout,"0");
				}
			}
			fprintf(stdout,"%i", get(P->list));
			moveNext(P->list);
		}
	}
	fprintf(stdout,"\n");
}
//helper function that checks 0
void zeroCheck(BigInteger N)
{
	moveFront(N->list);
	while(get(N->list) == 0 && length(N->list) != 1)
	{
		moveNext(N->list);
		deleteFront(N->list);
	}
	//printf("length is: %i\n", length(N->list));
	moveBack(N->list);
	if(length(N->list) == 1 && get(N->list) == 0)
	{
		N->sign = 0;
	}
}
