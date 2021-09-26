#------------------------------------------------------------------------------
# Alan Szeto
# 1672580
# pa2
# Makefile for CSE 101 Programming Assignment 2
#
#       make                   makes Arithmetic
#     				           makes BigIntegerTest
#------------------------------------------------------------------------------

Arithmetic : Arithmetic.o BigInteger.o List.o
	gcc -o Arithmetic Arithmetic.o BigInteger.o List.o

Arithmetic.o : Arithmetic.c BigInteger.h List.h
	gcc -c -std=c99 -Wall Arithmetic.c

BigIntegerTest : BigIntegerTest.o BigInteger.o List.o
	gcc -o test BigIntegerTest.o BigInteger.o List.o -lm
	
BigIntegerTest.o : BigIntegerTest.c BigInteger.h List.h
	gcc -c -std=c99 -Wall BigIntegerTest.c
	
BigInteger.o : BigInteger.c BigInteger.h List.h
	gcc -c -std=c99 -Wall BigInteger.c
	
List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c
	
# valgrind : valgrind 
	# --track-origins=yes --leak-check=full Arithmetic.c

clean :
	rm -f valgrind Arithmetic.o Arithmetic BigIntegerTest BigIntegerTest.o BigInteger.o List.o 
 