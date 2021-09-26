#------------------------------------------------------------------------------
#  Makefile for List ADT
#
#      make             makes ListTest
#      make clean       removes object files
#
#------------------------------------------------------------------------------

/*
LextTest : LextTest.o List.o
	gcc -o LextTest LextTest.o List.o 

LextTest.o : List.h ListTest.c
	gcc -c -std=c99 -Wall LextTest.c

List.o : List.h List.c
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f LextTest LextTest.o List.o
*/
