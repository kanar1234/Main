//-----------------------------------------------------------------------------
// Alan Szeto
// 1672580
// pa4
// List.c
// Implementation file for GraphTest ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>

#include "Graph.c"
#include "List.c"

int main(int argc, char* argv[])
{
   int i, n=8;
   List L = newList();
   Graph G = newGraph(n);
   Graph G1=NULL, G2=NULL;

   for(i=1; i<=n; i++) append(L, i);
   addArc(G, 1,1);
   addArc(G, 1,2);
   addArc(G, 2,3);
   addArc(G, 2,7);
   addArc(G, 3,1);
   addArc(G, 3,2);
   addArc(G, 3,5);
   addArc(G, 6,6);
   addArc(G, 6,8);
   addArc(G, 8,1);
   addArc(G, 8,2);

   fprintf(stdout,"Number of verticies of G: %d \n\n", getOrder(G));
   fprintf(stdout,"Adjacency Matrix\n");
   printGraph(stdout, G);

   fprintf(stdout, "DFS(G)\n");	
   DFS(G, L);
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++)
   {
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   fprintf(stdout, "Stack\n");
   printList(stdout, L);
   fprintf(stdout, "\n");

   G1 = transpose(G);
   G2 = copyGraph(G);
   fprintf(stdout, "\n");
   fprintf(stdout,"copyGraph(G)\n");
   printGraph(stdout, G2);
   fprintf(stdout, "\n");
   fprintf(stdout,"transpose(G)\n");
   printGraph(stdout, G1);
   fprintf(stdout, "\n");

   fprintf(stdout, "DFS(transpose(G))\n");
   DFS(G1, L);
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++)
   {
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G1, i), getFinish(G1, i), getParent(G1, i));
   }
   fprintf(stdout, "\n");
   fprintf(stdout, "Stack\n");
   printList(stdout, L);
   fprintf(stdout, "\n");

   freeList(&L);
   freeGraph(&G);
   freeGraph(&G1);
   freeGraph(&G2);
   return(0);
}