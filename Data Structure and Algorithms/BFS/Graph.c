//-----------------------------------------------------------------------------
// Alan Szeto
// 1672580
// pa3
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

#define WHITE 1
#define GRAY 2
#define BLACK 3
//--------------------------------------------

/*** Constructors-Destructors ***/

struct GraphObj
{
   List *adj; //adjacency list
   int *col; //color
   int *p; //parent
   int *d; //distance
   int order; 
   int size; 
   int source;
};

//newGraph(int n)
//creates a new graph of order n, size 0, and NIL as the source
Graph newGraph(int n)
{
    Graph G = malloc(sizeof(struct GraphObj));
    G->adj = calloc(n+1, sizeof(List));
    G->col = calloc(n+1, sizeof(int));
    G->p = calloc(n+1, sizeof(int));
    G->d = calloc(n+1, sizeof(int));
    G->order = n;
    G->size = 0;
    G->source = NIL;
	for(int i = 0; i < n+1; i++)
	{
		G->adj[i] = newList();
		G->col[i] = WHITE;
		G->p[i] = NIL;
		G->d[i] = INF;
	}
	return G;
}

//freeGraph()
//frees memory 	
void freeGraph(Graph* pG)
{
	if(pG!=NULL && *pG!=NULL)
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
	}
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

int getSource(Graph G)
{
	if(G == NULL)
	{
		printf("Error: calling getSource() on NULL Graph reference\n");
		exit(1);
	}
	return G->source;
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

int getDist(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Error: calling getDist() on NULL Graph reference\n");
		exit(1);
	}
	if(u < 1 || u > getOrder(G))
	{
		printf("Error: calling getDist() on out of bound reference\n");
		exit(1);
	}
	
	return G->d[u];
}

void getPath(List L, Graph G, int u)
{
	if(G == NULL)
    {
		printf("Error: calling getPath() on NULL Graph reference\n");
		exit(1);
    }
    if(getSource(G) == NIL)
    {
		printf("Error: calling getPath() on NIL reference\n");
		exit(1);
    }
    if(u < 1 || u > getOrder(G))
    {
		printf("Error: calling getPath() on out of bound reference\n");
		exit(1);
    }
	
    if(u == G->source)
    {
        append(L, G->source);
    }
    else if(G->p[u] == NIL)
    {
        append(L, NIL);
    }
    else
    {
        getPath(L, G, G->p[u]);
        append(L,u);
    }
}
/*** Manipulation procedures ***/
void makeNull(Graph G)
{
	if(G == NULL)
	{
		printf("Error: G is already NULL\n");
		exit(1);
	}
	
	for(int i = 0; i < G->order + 1; i++)
	{
		clear(G->adj[i]);
	}
}

//adds a new edge joining u and v
void addEdge(Graph G, int u, int v)
{
	if(G == NULL)
	{
		printf("Error: calling addEdge() on NULL Graph reference");
		exit(1);
	}
	if(u < 1 || u > getOrder(G))
    {
        printf("Out of bounds error for edge u\n");
        exit(1);
    }
    if(v < 1 || v > getOrder(G))
    {
        printf("Out of bounds error for edge v\n");
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
	if(u < 1 || u > getOrder(G))
    {
        printf("Out of bounds error for edge u\n");
        exit(1);
    }
    if(v < 1 || v > getOrder(G))
    {
        printf("Out of bounds error for edge v\n");
        exit(1);
    }
	
	moveFront(G->adj[u]);
	//moves to corresponding spot in adjacency list
    while(index(G->adj[u]) > -1 && v > get(G->adj[u]))
    {
        moveNext(G->adj[u]);
    }
	
	//adds vertex to adjacenct list of u 
    if(index(G->adj[u]) ==  -1)
    {
        append(G->adj[u], v);
    }
    else 
	{
        insertBefore(G->adj[u], v);
	}
	
    G->size++;
}

void BFS(Graph G, int s)
{
	if(G == NULL)
    {
        printf("Error: Graph doesn't exist\n");
        exit(1);
    }
    if(s < 1 || s > getOrder(G))
    {
        printf("Out of bounds error for edge s\n");
    }
	
	//turns parent to nil, distance to inf, and color to white for all vertices in the graph
    for(int i = 0; i < (G->order +1); i++)
    {
        G->p[i] = NIL;
        G->d[i] = INF;
        G->col[i] = WHITE;
    }

	//sets source to s and adds it to the top of the bfs graph 
    List list = newList();
    G->source = s;
    G->col[s] = GRAY;
    G->d[s] = 0;
    prepend(list,s);
	  
	//performs bfs
    while(length(list) > 0)
    {
        int a = back(list);
        deleteBack(list);

        moveFront(G->adj[a]);

		//goes through the adjacency list and prepends 
		//adjacennt vertice not found into the temporary list
        while(index(G->adj[a]) > -1)
        {
            int b = get(G->adj[a]);

            if(G->col[b] == WHITE)
            {
                G->col[b] =  GRAY;
                G->p[b] = a;
                G->d[b] = G->d[a] + 1;
                prepend(list,b);
            }
            moveNext(G->adj[a]);
        }
    }
    freeList(&list);
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G)
{
	if(G == NULL)
	{
		printf("Error: calling printGraph() on NULL Graph reference\n");
		exit(1);
	}
	
	for(int i = 1; i < getOrder(G)+1; i++)
	{
		fprintf(out,"%d: ", i);
		printList(out, G->adj[i]);
		fprintf(out,"\n");
	}
}