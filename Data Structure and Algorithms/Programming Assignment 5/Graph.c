//-----------------------------------------------------------------------------
// Alan Szeto
// 1672580
// pa4
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2
//--------------------------------------------

/*** Constructors-Destructors ***/

struct GraphObj
{
   List *adj; //adjacency list
   int *col; //color
   int *p; //parent
   int *d; //discover
   int *f; //finish
   int order; 
   int size; 
   int time;
};

//newGraph(int n)
//creates a new graph of order n, size 0, and NIL as the source
Graph newGraph(int n)
{
    Graph graph = malloc(sizeof(struct GraphObj));
    graph->adj = calloc(n+1, sizeof(List));
    graph->col = calloc(n+1, sizeof(int));
    graph->p = calloc(n+1, sizeof(int));
    graph->d = calloc(n+1, sizeof(int));
    graph->f = calloc(n+1, sizeof(int));
    graph->order = n;
    graph->size = 0;
    graph->time = UNDEF;
	for(int i = 0; i < n+1; i++)
	{
		graph->adj[i] = newList();
		graph->col[i] = WHITE;
		graph->p[i] = NIL;
		graph->d[i] = UNDEF;
		graph->f[i] = UNDEF;
	}
	return graph;
}

//freeGraph()
//frees memory 	
void freeGraph(Graph* pG)
{
	Graph graph = *pG;
	for(int i = 0; i < graph->order+1; i++)
	{
		freeList(&(graph->adj[i]));
	}
	free(graph->adj);
	free(graph->col);
	free(graph->p);
	free(graph->d);
	free(graph->f);
	free(*pG);
	*pG = NULL;
}

/*** Access functions ***/
int getOrder(Graph G)
{
	if(G == NULL)
	{
		printf("Error: calling getOrder() on NULL Graph reference\n");
		exit(1);
	}
	return G->order;
}

int getSize(Graph G)
{
	if(G == NULL)
	{
		printf("Error: calling getSize() on NULL Graph reference\n");
		exit(1);
	}
	return G->size;
}

int getParent(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Error: calling getParent() on NULL Graph reference\n");
		exit(1);
	}
	if(u < 1 || u > getOrder(G))
	{
		printf("Error: calling getParent() on out of bound reference\n");
		exit(1);
	}
	return G->p[u];
}

int getDiscover(Graph G, int u) /* Pre: 1<=u<=n=getOrder(G) */
{
	if(G == NULL)
	{
		printf("Error: calling getDiscover() on NULL Graph reference\n");
		exit(1);
	}
	if(u < 1 || u > getOrder(G))
	{
		printf("Error: calling getDiscover() on out of bound reference\n");
		exit(1);
	}
	return G->d[u];
	
}

int getFinish(Graph G, int u) /* Pre: 1<=u<=n=getOrder(G) */
{
	if(G == NULL)
	{
		printf("Error: calling getFinish() on NULL Graph reference\n");
		exit(1);
	}
	if(u < 1 || u > getOrder(G))
	{
		printf("Error: calling getFinish() on out of bound reference\n");
		exit(1);
	}
	return G->f[u];
	
}

/*** Manipulation procedures ***/

//adds a new edge joining u and v
void addEdge(Graph G, int u, int v)
{
	if(G == NULL)
	{
		printf("Error: calling addEdge() on NULL Graph reference");
		exit(1);
	}
	
	//adds directed edges going both ways from u to v
	addArc(G,u,v);
	addArc(G,v,u);
	
	G->size--;
}

//adds a directed edge from u to v 
void addArc(Graph G, int u, int v)
{
	if(G == NULL)
	{
		printf("Error: calling addArc() on NULL Graph reference\n");
		exit(1);
	}
	
	
	List L = G->adj[u];
	
	if(length(L) == 0)
	{
		append(L,v);
		G->size++;
		return;
	}
	moveFront(L);
	while(index(L) != -1)
	{
		if(v < get(L))
		{
			insertBefore(L,v);
			G->size++;
			return;
		}
		else if(v == get(L))
		{
			return;
		}
		moveNext(L);
	}
	append(L, v);
	G->size++;
}

//	if(length(G->adj[u]) > 0)
//helper function for DFS
void visit(Graph G, List L, int n)
{	
	if(G == NULL)
	{
		printf("Error: calling visit() on NULL Graph reference\n");
		exit(1);
	}
	
	
	int y;
	G->col[n] = GRAY;
	G->time++;
	G->d[n] = G->time;
	List L1 = G->adj[n];
	moveFront(L1);
	while(index(L1) != -1)
	{
		y = get(L1);
		if(G->col[y] == WHITE)
		{
			G->p[y] = n;
			visit(G, L, y);
		}
		moveNext(L1);
	}
	G->col[n] = BLACK;
	G->time++;
	G->f[n] = G->time;
	prepend(L,n);
}

void DFS(Graph G, List S)
{
	if(G == NULL)
    {
		printf("Error: calling DFS() on NULL Graph reference\n");
        exit(1);
    }
	/* if(length(S) != getOrder(G))
    {
		printf("Error: calling DFS() on graphs with unequal sizes\n");
        exit(1);
    } */
	int n;
	List L = copyList(S);
	clear(S);
	
	for(int i = 1; i <= G->order; i++)
	{
		G->col[i] = WHITE;
		G->p[i] = NIL;
		G->d[i] = UNDEF;
		G->f[i] = UNDEF;
	}
	
	G->time = 0;
	moveFront(L);
	while(index(L) != -1)
	{
		n = get(L);
		if(G->col[n] == WHITE)
		{
			visit(G,S,n);
		}
		moveNext(L);
	}
	freeList(&L);
}

/*** Other operations ***/
Graph transpose(Graph G)
{
	if(G == NULL)
    {
		printf("Error: calling DFS() on NULL Graph reference\n");
        exit(1);
    }
	
	Graph G1 = newGraph(getOrder(G));
	for(int i = 1; i < getOrder(G)+1; i++)
	{
		moveFront(G->adj[i]);
		while(index(G->adj[i]) > -1)
		{
			addArc(G1, get(G->adj[i]),i);
			moveNext(G->adj[i]);
		}
	}
	return G1;
}


Graph copyGraph(Graph G)
{
	if(G == NULL)
    {
		printf("Error: calling DFS() on NULL Graph reference\n");
        exit(1);
    }
	
	Graph G1 = newGraph(getOrder(G));
	for(int i = 1; i <getOrder(G)+1; i++)
	{
		moveFront(G->adj[i]);
		while(index(G->adj[i]) > -1)
		{
			addArc(G1,i, get(G->adj[i]));
			moveNext(G->adj[i]);
		}
	}
	return G1;
}

void printGraph(FILE* out, Graph G)
{
	if(out == NULL || G == NULL)
	{
		printf("Error: calling printGraph() on NULL Graph reference\n");
		exit(1);
	}

	for(int i = 1; i < getOrder(G)+1; i++)
	{
		fprintf(out, "%d: ", i);
		printList(out, G->adj[i]);
		fprintf(out, "\n");
	}
}