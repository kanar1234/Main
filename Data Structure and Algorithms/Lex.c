//-----------------------------------------------------------------------------
// Alan Szeto
// 1672580
// pa1
// ListADT client that sorts the lines of an input file
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "List.h"

List insertionSort(char** a, int n){
    int i;
    List p = newList();

    //appends first element
    if ( n>0 ){
		append(p, 0);
		}
    for ( i=1; i<n; i++ ){
		
        char *comp = a[i];
        int pLen = length(p)-1;
        moveFront(p);
		//move cursor to end of p
        while( index(p)!=pLen ){
            moveNext(p);
        }
		//compares a and p and moves cursor
		//right if a<p 
        while( pLen>-1 && strcmp(comp, a[get(p)])<0 ){
            pLen--;
            movePrev(p);
        }
		//if the cursor goes to the null, put 
		//a to the front of p
        if(index(p) == -1){
            prepend(p, i);
		//otherwise inserts a to right of cursor in p
        } else {
            insertAfter(p, i);
        }
    }
    return p;
}

//duplicates string
char *strdup (const char *p) {
    char *q = malloc(strlen(p)+1);
    if (q == NULL){
		return NULL;
	}
    strcpy(q,p);
    return q;
}

//reads the file into an array of strings
char** read(FILE* in, int n){
    char** p = calloc(n, sizeof(char**));
    char arr[100];
    for(int i = 0; i < n; i++){
        fgets(arr, 100, in);
        p[i] = strdup(arr);
    }
    return p;
}

int main(int argc, char* argv[]){
    char arr[100];
    int count = 0;
    int i;

    //opens input file from argv[1]
    FILE* in = fopen(argv[1], "r");
    //opens output file from argv[2]
    FILE* out = fopen(argv[2], "w");

    //counts number of lines
    while( fgets(arr, 100, in) != NULL) {
        count++;
    }

    //closes input file
    fclose(in);
    //reopens input file
    in = fopen(argv[1], "r");

    //creates an array of string from input file
    char** str = read(in, count);

    List L = insertionSort(str, count);

    moveFront(L);
    for( i=0; i<count; i++ ){
        fprintf(out, "%s", str[get(L)]);
        moveNext(L);
    }

    fclose(in);
    fclose(out);

    for( i=0; i<count; i++ ){
        free(str[i]);
    }
    free(str);
    freeList(&L);
    return(0);
}


