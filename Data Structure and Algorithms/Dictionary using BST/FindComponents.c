//-----------------------------------------------------------------------------
// Alan Szeto
// 1672580
// pa4
// FindComponents.c
// Implementation file for FindComponents ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "Graph.h"
#define NUM 69
int main(int argc, char * argv[])
{
	int size, num, scc = 0;
	char line[NUM];
    FILE *in;
    FILE *out;
	
	if(argc != 3)
	{
		printf("Error: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	
	//opens file to read and write 
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	
	if(in == NULL)
	{
		printf("Error: unable to open %s \n", argv[1]);
		exit(1);
	}
	if(out == NULL)
	{
		printf("Error: unable to open %s \n", argv[2]);
		exit(1);
	}
	
	fgets(line, NUM, in);
	
	//scans file
	sscanf(line, "%i", &size);
	
	Graph graph = newGraph(size);
	
	while(fgets(line, NUM, in) != NULL)
	{
		int a,b = 0;
		sscanf(line, "%d %d", &a, &b);
		if(a == 0 && b == 0)
		{
			break;
		}
		addArc(graph, a, b);
	}
	
	fprintf(out,"Adjacency list representation of G:\n");
	printGraph(out, graph);
	List L = newList();
	for(int i = 1; i < size+1; i++)
	{
		append(L, i);
	}
	DFS(graph, L);
	Graph Transpose;
	Transpose = transpose(graph);
	DFS(Transpose, L);
	moveFront(L);
	while(index(L) > -1)
	{
		if(getParent(Transpose, get(L)) == NIL)
		{
			scc++;
		}
		moveNext(L);
	}
	
	List sccList[scc];
	for(int i = 0; i < scc; i++)
	{
		sccList[i] = newList();
	}
	
	num = scc;
	moveFront(L);
	while(index(L) > -1)
	{
		if(getParent(Transpose, get(L)) == NIL)
		{
			num--;
		}
		if(num == scc)
		{
			break;
		}
		append(sccList[num], get(L));
		moveNext(L);
	}
	fprintf(out,"\n");
	fprintf(out, "G contains %d strongly connected components:\n", scc);
	for(int i = 0; i < scc; i++)
	{
		fprintf(out, "Component %d: ", i+1);
		printList(out, sccList[i]);
		fprintf(out,"\n");
		freeList(&(sccList[i]));
	}	
}