#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "List.h"
#define MAX_LEN 160

List insertionSort(char** a, int n){
    int i;
    List p = newList();

    // appends first element
    if ( n>0 ){ 
		append(p, 0);
	}
	//insertion sort
    for ( i=1; i<n; i++ ){
        char *comp = a[i];
        int  k = i - 1;
        moveFront(p);
        while( index(p)!= k ){
            moveNext(p);
        }
        while( strcmp(comp, a[get(p)])<0 && j>-1 ){
            j--;
            movePrev(p);
        }
        if(index(p) == -1){
            prepend(p, i);
        } 
		else {
            insertAfter(p, i);
        }
    }
    return p;
}