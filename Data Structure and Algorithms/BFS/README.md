Make:
Creates the Graph ADT

How to run: 


Description
Graph.c:
Creates Graph ADT

Graph.h:
Header for the Graph ADT

FindPath.c
Prints the adjacency list, BFS, and SSSP if it exists

List.c:
Creates a doubly linked list and the List ADTs

List.h:
Header for List.c

GraphTest.c:
Given - Tests the Graph ADT

Makefile:
Given - Compiles the program

------------------------------Graph Functions------------------------------

-----Exported type -----

//Graph reference type

typedef struct GraphObj* Graph;

-----Constructors-Destructors-----

//Returns a reference to a new Graph object in the zero state

Graph newGraph(int n);

//Frees heap memory associated with pG and sets it to null 

void freeGraph(Graph* pG);

-----Access functions-----

//Returns the order of the graph G

int getOrder(Graph G);

//Returns the size of the graph G

int getSize(Graph G);

//Returns the source of the Graph G

int getSource(Graph G);

//Returns the parent of u in Graph G

int getParent(Graph G, int u);

//Returns the distance of u in Graph G

int getDist(Graph G, int u);

-----Manipulation procedures-----

//Removes all edges from Graph G

void makeNull(Graph G);

//Adds a directed edge from point u to v in Graph G

void addEdge(Graph G, int u, int v);

//Adds an arc from point u to v in Graph G

void addArc(Graph G, int u, int v);

//Performs BFS on graph G with s as its source

void BFS(Graph G, int s);

-----Other operations-----

//prints Graph G onto the terminal

void printGraph(FILE* out, Graph G);
