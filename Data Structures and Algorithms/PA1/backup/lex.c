//check that there are two command lines otherwise quit with error
//count number of lines n in the input filelength
//create a string array of length n and read it in string then put them into the array
//create a list using the above string array

//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "List.h"
List insertionSort(char** a, int n){
	int j;
	List p = newList();
	char *temp = a[0]
	//appends the first element
	if ( n > 0){
		append(p, temp);
	}
	//insertion sort
	for (j = 1; j < n; j++){
		//temp = j from 1 to n
		temp = a[j];
		
		//i = index of p
		int i = j-1;
		
		//gets the last value of p 
		//checks if a[j] is greater than 
		//p[index-1]
		//else checks if a[j] < p[i to n]
		moveBack(p);
		if(a[j] >= p[i]){
			append(p, temp);
		}
		else{
			while  (i>-1 && strcmp(temp, a[get(list)])<0){
			i--;
			movePrev(p);
			}
			if (index(p) = -1){
				prepend(p, temp);
			}
			else{
				insertAfter(p, temp);
			}
		}
	}	
	return p;
}