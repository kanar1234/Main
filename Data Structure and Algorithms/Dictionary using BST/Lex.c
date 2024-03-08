//-----------------------------------------------------------------------------
// Alan Szeto
// 1672580
// pa5
// Dictionary ADT client that sorts the lines of an input file
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"

#define MAX_LEN 420

int main(int argc, char * argv[]){

	int n = 0;
	int count = 0;
	FILE *in, *out;
	char line[MAX_LEN];

	// check command line for correct number of arguments
	if( argc != 3 ){
	  printf("Usage: %s <input file> <output file>\n", argv[0]);
	  exit(1);
	}

	// open files for reading and writing 
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if( in==NULL ){
	  printf("Unable to open file %s for reading\n", argv[1]);
	  exit(1);
	}
	if( out==NULL ){
	  printf("Unable to open file %s for writing\n", argv[2]);
	  exit(1);
	}
	while(fgets(line, MAX_LEN, in) != NULL)
    {
        count++;
    }
	//printf("count is %i\n",count);
	rewind(in);
	char strArray[count][MAX_LEN];
		
	//copies the lines in the in file to an array of strings
	while(fgets(line, MAX_LEN, in) != NULL)
	{
		strcpy(strArray[n], line);
		n++;
	}
	strcat(strArray[count], "\n");
	Dictionary D = newDictionary(0);
	for(int i = 0; i <n; i++)
	{
		insert(D, strArray[i], i);
	}
	printDictionary(out,D);
	/* close infiles */
	fclose(in);
	fclose(out);
	freeDictionary(&D);
	return(0);
}