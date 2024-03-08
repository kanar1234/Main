//-----------------------------------------------------------------------------
// Alan Szeto
// 1672580
// pa3
// GraphClient.c
// Implementation file for GraphClient ADT
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include"Graph.h"
int main(int argc, char* argv[]){
    int i, s, max, min, d, n=35;
   Graph graph = newGraph(30);
   int j = 0;
   for(j = 1; j < 30; ++j) {
      if(j % 2 == 1)
         addEdge(graph, j, 30 - j);
      else if(j % 3 != 1)
         addArc(graph, j, 30 - j);
   }

   for(i = 1; i < 30; ++i) {
      BFS(graph, i);
      for(j = 1; j < 30; ++j) {
         int k = getDist(graph, j);
         if(k != INF)
            printf("Distance: %d-%d: %d\n", i, j, k);
      }
   }

   BFS(graph, 5);
   List A = newList();
   getPath(A, graph, 25);
   printf("\n");
   printf("Path from 5 to 25: ");
   printList(stdout, A);
   printf("\n");

   BFS(graph, 1);
   List B = newList();
   getPath(B, graph, 29);
   printf("\n");
   printf("Path from 1 to 29: ");
   printList(stdout, B);
   printf("\n");
   

   freeList(&A);
   freeList(&B);
   freeGraph(&graph);

   List  C = newList(); // central vertices 
   List  P = newList(); // peripheral vertices 
   List  E = newList(); // eccentricities 
   Graph G = NULL;

   // Build graph G 
   G = newGraph(n);
   for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
   addEdge(G, 9, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);

   // Print adjacency list representation of G
   
   printGraph(stdout, G);

   // Calculate the eccentricity of each vertex 
   
   for(s=1; s<=n; s++){
      BFS(G, s);
      max = getDist(G, 1);
      for(i=2; i<=n; i++){
         d = getDist(G, i);
         max = ( max<d ? d : max );
      }
      append(E, max);
   }

   // Determine the Radius and Diameter of G, as well as the Central and 
   // Peripheral vertices.
   
   append(C, 1);
   append(P, 1);
   min = max = front(E);
   moveFront(E);
   moveNext(E);
   for(i=2; i<=n; i++){
      d = get(E);
      if( d==min ){
         append(C, i);
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, i);
      }
      if( d==max ){
         append(P, i);
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
      }
      moveNext(E);
   }

   // Print results 
   printf("\n");
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");

   // Free objects 
   freeList(&C);
   freeList(&P);
   freeList(&E);
   freeGraph(&G);

   return(0);
}