//-----------------------------------------------------------------------------
// Alan Szeto
// 1672580
// pa1
// BigInteger.c
// Implementation file for BigInteger ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <string.h>
#include "BigInteger.h"
#include "List.h"
#define power 9

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
	B->sign = 1;
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
		while( comp == 0 || index(A->list) != -1)
		{
			if(get(A->list) == get(B->list))
			{
				moveNext(A->list);
				moveNext(B->list);
			}
			else
			{
				if(get(A->list) > get(B->list))
				{
					comp = 1;
				}
				else
				{
					comp = -1;
				}
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
	char c = s[0];
	long toLong = 0;
	char* s2 = malloc(power);
	int counter = 0;
	int x = 0;
	int base = 0;
	int extra = 0;
	BigInteger B = newBigInteger();
	if(c == '-')
	{
		B->sign = -1;
		extra = 1;
	}
	else if(c == '+')
	{
		B->sign = 1;
		extra = 1;
	}
	else
	{
		B->sign = 1;
	}	
	counter += extra;
	for(int i = 0; i < (strlen(s)+power-1-extra)/power; i++)
	{
		if(length(B->list) == 0 && (strlen(s)-extra)%power != 0)
		{
			base = (strlen(s)-extra)%power;
		}
		else
		{
			base = power;
		}
		for(int j = 0; j < base; j++)
		{
			s2[j] = s[counter];
			counter++;
		}		
		while(s2[x] == '0')
		{
			s2[x] = '\0';
			x++;
		}
		x = 0;
		toLong = strtol(s2, NULL, 0);
		prepend(B->list, toLong);
	}
	moveBack(B->list);
	set(B->list, abs(get(B->list)));
	moveFront(B->list);
	if(get(B->list) == 0 && length(B->list) == 1)
	{
		B->sign = 0;
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
	moveFront(A->list);
	moveFront(B->list);
	int larger = largerCheck(A,B);
	
	if(A->sign == -1 || B->sign == -1)
	{
		//-A - B == -(A+B)
		if(A->sign == -1 && B->sign == -1)
		{
			BigInteger Ac = copy(A);
			Ac->sign = 1;
			BigInteger Bc = copy(B);
			Bc->sign = 1;
			add(S,Ac,Bc);
			S->sign = -1;
		}
		//-A+B sign depends on the larger value of A and B
		else if(A->sign == -1)
		{
			BigInteger Ac = copy(A);
			Ac->sign = 1;
			subtract(S,B,Ac);
		}
		//A-B sign depends on the larger of A and B
		else
		{
			BigInteger Bc = copy(B);
			Bc->sign = 1;
			subtract(S,A,Bc);
		}
	}
	else
	{
		moveFront(A->list);
		moveFront(B->list);
		while(index(A->list) != -1 || index(B->list) != -1)
		{
			if(index(A->list) == -1)
			{
				append(S->list, get(B->list));
				moveNext(B->list);
			}
			else if(index(B->list) == -1)
			{
				append(S->list, get(A->list));
				moveNext(A->list);
			}
			else
			{
				append(S->list,get(A->list) + get(B->list));
				moveNext(A->list);
				moveNext(B->list);
			}
		}	
		//A+B
		if(A->sign == B->sign)
		{
			S->sign = 1;
		}
		//A+(-B) vs -A+B
		else if(larger) //B > A
		{
			if(A->sign == -1)
				S->sign = 1;
			else if(A->sign == 0 || B->sign == 0)
			{
				if(A->sign == 0)
					S->sign = B->sign;
				else
					S->sign = A->sign;
			}
			else
				S->sign = -1;
		}
		else
		{
			if(A->sign == -1)
				S->sign = -1;
			else if(A->sign == 0 || B->sign == 0)
			{
				if(A->sign == 0)
					S->sign = B->sign;
				else
					S->sign = A->sign;
			}
			else
				S->sign = 1;
		}
	}

	moveFront(S->list);
	for(int i = 0; i < length(S->list)-1; i++)
	{
		overflow = get(S->list)/base;
		set(S->list, get(S->list)%base);
		moveNext(S->list);
		set(S->list, get(S->list) + overflow); 
	}
	zeroCheck(S);
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
	moveBack(A->list);
	moveBack(B->list);
	
	//if B > A, perform subtract B,A
	int larger = largerCheck(A,B);

//performs (-B)-(-A) instead of A-B => -B + A for easier calculations
	if(larger == 1)
	{
		//swaps sign of A and B
		BigInteger Ac = copy(A);
		BigInteger Bc = copy(B);
		negate(Ac);
		negate(Bc);
		subtract(D,Bc,Ac);
	}
	else
	{		
		//note: length(A) > length(B)
		//Condition -A - B == -(A+B)
		if(A->sign == -1 && B->sign == 1)
		{
			BigInteger Ac = copy(A);
			negate(Ac);
			add(D,Ac,B);
			D->sign = -1;
		}
		//Condition A - (-B) == A+B
		else if(A->sign == 1 && B->sign == -1)
		{
			BigInteger Bc = copy(B);
			negate(Bc);
			add(D,A,Bc);
			D->sign = 1;
		}
		else if(equals(A,B) && A->sign == B->sign)
		{
			makeZero(D);
		}
		//Condition A - B or -A + B where A > B
		else
		{
			moveFront(A->list);
			moveFront(B->list);
			while(index(A->list) != -1 || index(B->list) != -1)
			{
				//if B reaches end of list, continue with A
				if(index(B->list) == -1)
				{
					append(D->list, get(A->list));
					moveNext(A->list);
				}
				//appends A-B then moves next in both lists
				else
				{
					append(D->list,get(A->list) - get(B->list));
					moveNext(A->list);
					moveNext(B->list);
				}
			}
			//A>B, A-B and -A-(-B)
			if(A->sign == -1 && B->sign == -1)
			{
				D->sign = -1;
			}
			else if(A->sign == 0 || B->sign == 0)
			{
				if(A->sign == 0)
					D->sign = B->sign;
				else
					D->sign = A->sign;
			}
			else
			{
				D->sign = 1;
			}
		}
	}

	moveFront(D->list);
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
		moveNext(D->list);
		set(D->list, get(D->list) - underflow); 
	}
	zeroCheck(D);
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
	BigInteger X = newBigInteger();
	BigInteger Y = newBigInteger();
	clear(P->list);
	int overflow = 0;
	int counter = 0;
	
	int larger = largerCheck(A,B);
	if(A->sign == 0 || B->sign == 0)
	{
		append(Y->list,0);
		P->list = copyList(Y->list);
	}
	else{
	if(larger == 1)
	{
		multiply(P,B,A);
	}
	else
	{
		append(Y->list, 0);
		moveFront(A->list);
		moveFront(B->list);
		
		while(index(B->list) != -1)
		{
			append(X->list, get(A->list)*get(B->list));
			moveNext(A->list);
			if(index(A->list) == -1)
			{
				moveNext(B->list);
				Y = sum(X,Y);
				clear(X->list);
				moveFront(A->list);
				counter++;
				for(int i = 0; i < counter; i++)
				{
					append(X->list, 0);
				}
			}
		}
		P->list = copyList(Y->list);
		moveFront(P->list);
		for(int i = 1; i < length(P->list); i++)
		{
			overflow = get(P->list)/base;
			set(P->list, get(P->list)%base);
			moveNext(P->list);
			set(P->list, get(P->list) + overflow); 
		}
		
		//if the last value is greater than base, fix it
		moveBack(P->list);
		int x = 0;
		int y = 0;
		while(get(P->list) >= base)
		{
			x = get(P->list)/base;
			y = get(P->list)%base;
			set(P->list, y);
			append(P->list, x);
			moveBack(P->list);
		}
		if(A->sign != B->sign)
		{
			P->sign = -1;
		}
		else
		{
			P->sign = 1;
		}
	}}
	
	zeroCheck(P);
	freeBigInteger(&X);
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
void printBigInteger(FILE* out, BigInteger N)
{
	if(length(N->list) == 0 )
	{
		fprintf(out,"Length is too short\n");
	}
	else if(N->sign == 0)
		printf("0\n");
	else
	{
		BigInteger P = newBigInteger();
		if(N->sign == -1)
			printf("-");
		moveFront(N->list);
		while(index(N->list) != -1)
		{
			prepend(P->list, get(N->list));
			moveNext(N->list);
		}
		moveFront(P->list);
		while(index(P->list) != -1)
		{
			printf("%li", get(P->list));
			moveNext(P->list);
		}
		printf("\n");
	}
	
}
//helper function that checks 0
void zeroCheck(BigInteger N)
{
	moveBack(N->list);
	while(get(N->list) == 0 && length(N->list) != 1)
	{
		moveBack(N->list);
		deleteBack(N->list);
	}
	moveFront(N->list);
	if(length(N->list) == 1 && get(N->list) == 0)
	{
		N->sign = 0;
	}
}

//helper function that returns 1 if B>A otherwise 2
int largerCheck(BigInteger A, BigInteger B)
{
	//if B>A return 1 else return 0
	int larger = 0;
	if(equals(A,B))
		larger = 2;
	if((length(B->list) > length(A->list)))
		larger = 1;
	if((length(B->list) < length(A->list)))
		larger = 2;
	moveBack(A->list);
	moveBack(B->list);
	while(larger == 0 && index(A->list) != -1 && index(B->list) != -1)
	{
		if (get(A->list) < get(B->list))
			larger = 1;
		else
			larger = 2;
	}
	return larger;
}
