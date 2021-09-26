#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 3
#
#  make                     makes GraphTest
#  make GraphClient         makes GraphClient
#  make clean               removes binaries
#  make checkFind           tests GraphTest for memory leaks on in3
#  make checkClient         tests GraphClient for memory leaks
#------------------------------------------------------------------------------

LIBS 			= List Graph
LIBS_SRC 		= ${LIBS:=.c}
LIBS_HDR 		= ${LIBS:=.h}
LIBS_OBJ 		= ${LIBS:=.o}
EXEBIN 			= FindPath
ALL_OBJECTS		= ${LIBS_OBJ} ${EXEBIN:=.o}
LINK            = gcc -c -std=c99 -Wall
COMPILE         = gcc -o

all : EXEBIN

EXEBIN : ${EXEBIN:=.o} ${LIBS_OBJ}
	${COMPILE} ${EXEBIN} ${ALL_OBJECTS}

${EXEBIN:=.o} : ${EXEBIN:=.c} ${LIBS_HDR}
	${LINK} ${EXEBIN:=.c} 

${LIBS_OBJ} : ${LIBS_SRC} ${LIBS_HDR}
	${LINK} ${LIBS_SRC} 

clean :
	rm -f ${EXEBIN} ${ALL_OBJECTS}
