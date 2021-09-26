//-----------------------------------------------------------------------------
// Alan Szeto
// 1672580
// pa3
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#define MAX_LEN 69
     
int main(int argc, char * argv[]){

   int order,v1,v2 = 0;
   char line[MAX_LEN];
   FILE *in, *out;
   List L = newList();

   //checks command line for correct number of arguments
   if( argc != 3 ){
      printf("Wrong number of command lines\n");
      exit(1);
   }

   //opens read and write files
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
   //scans the in file
   fgets(line,MAX_LEN,in);
   sscanf(line,"%i",&order);
   //create a graph of order amount of vertice
   Graph G = newGraph(order);
   
   //scans lines until it reaches 0 0
   while(fgets(line,MAX_LEN,in) != NULL){
	   sscanf(line,"%i%i",&v1,&v2);
	   if(v1 == 0){
		   break;
	   }
	   addEdge(G,v1,v2);
   }
   
   //print the adjacent list of each vertice
   printGraph(out,G);
   
   //Run BFS on the next lines until it reaches 0 0 and finds the SSSP if it exists
   while(fgets(line,MAX_LEN,in) != NULL){
	   fprintf(out,"\n");
	   sscanf(line,"%i%i",&v1,&v2);
	   if(v1 == 0){
		   break;
	   }
	   BFS(G,v1);
	   fprintf(out,"The distance from %i to %i is ", v1,v2);
	   if(getDist(G,v2) == INF){
		   fprintf(out,"infinity\n");
		   fprintf(out,"No %i-%i path exists\n",v1,v2);
	   }
	   else{
		   fprintf(out,"%i\n",getDist(G,v2));
		   fprintf(out,"A shortest %i-%i path is: ",v1,v2);
		   getPath(L,G,v2);
		   printList(out,L);
		   clear(L);
	   }
   }
   //close infiles
   fclose(in);
   fclose(out);
   
   //free the allocated memory
   freeList(&L);
   freeGraph(&G);;
   return(0);
}