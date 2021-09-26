#------------------------------------------------------------------------------
# Alan Szeto
# 1672580
# pa1
# Makefile for CSE 101 Programming Assignment 1
#
#       make                   makes Lex
#       make ListTest        makes ListTest
#------------------------------------------------------------------------------

MatrixTest : MatrixTest.o Matrix.o	
	gcc -o MatrixTest MatrixTest.c Matrix.o
	
MatrixTest.o : MatrixTest.c Matrix.h
	gcc -c -std=c99 -Wall MatrixTest.c

Matrix.o : Matrix.c Matrix.h
	gcc -c -std=c99 -Wall Matrix.c
	
List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c
	
clean :
	rm -f MatrixTest MatrixTest.o Matrix.o List.o 
 