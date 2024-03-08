//-----------------------------------------------------------------------------
// Alan Szeto
// 1672580
// pa6
// Dictionary ADT client that sorts the lines of an input file
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"

#define MAX_LEN 420

int main(int argc, char * argv[]){
	int* pI;
	Dictionary A = newDictionary(0);
	//testing delete
	insert(A, "m", &pI[0]);
        insert(A, "n", &pI[1]);
        insert(A, "o", &pI[2]);
        insert(A, "p", &pI[3]);
        insert(A, "q", &pI[4]);
        insert(A, "f", &pI[5]);
        insert(A, "e", &pI[6]);
		beginForward(A);
        delete(A, "e");
		
		printDictionary(stdout,A, "in");
		fprintf(stdout,"\n");
		printDictionary(stdout,A, "pre");
		fprintf(stdout,"\n");
		printDictionary(stdout,A, "post");
	//testing beginForward ------------------
	insert(A, "m", &pI[8]);
	printDictionary(stdout, A, in);
	fprintf(stdout,"\n");
    insert(A, "n", &pI[8]);
	printDictionary(stdout, A, in);
		fprintf(stdout,"\n");
        insert(A, "o", &pI[8]);
		printDictionary(stdout, A, in);
		fprintf(stdout,"\n");
        insert(A, "p", &pI[0]);
		printDictionary(stdout, A, in);
		fprintf(stdout,"\n");
        insert(A, "q", &pI[1]);
		printDictionary(stdout, A, in);
		fprintf(stdout,"\n");
        insert(A, "f", &pI[8]);
		printDictionary(stdout, A, in);
		fprintf(stdout,"\n");
        insert(A, "e", &pI[8]);
		fprintf(stdout,"\n");
		beginForward(A);
		fprintf(stdout,"beginforward is: \n");
		printDictionary(stdout, A, in);
		delete(A, "e");
		fprintf(stdout,"delete is: \n");
		printDictionary(stdout, A, in);
		
		
	//testing insert ------------------
	
	 insert(A, "a", &pI[8]);
	 printDictionary(stdout, A, in);
	fprintf(stdout,"\n");
     insert(A, "b", &pI[8]);
	 printDictionary(stdout, A, in);
	fprintf(stdout,"\n");
     insert(A, "c", &pI[8]);
	 printDictionary(stdout, A, in);
	fprintf(stdout,"\n");
     insert(A, "d", &pI[8]);
	 printDictionary(stdout, A, in);
	fprintf(stdout,"\n");
     insert(A, "e", &pI[8]);
	printDictionary(stdout, A, in);
	fprintf(stdout,"\n");
	printDictionary(stdout, A,pre);
	fprintf(stdout,"\n");
	printDictionary(stdout, A,"post");
	freeDictionary(&A);
}