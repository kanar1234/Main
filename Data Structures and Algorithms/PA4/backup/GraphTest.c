//-----------------------------------------------------------------------------
// Alan Szeto
// 1672580
// pa4
// GraphClient.c
// Implementation file for GraphClient ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   int i, s, max, min, d, n=35;
   List L = newList();
   List  C = newList(); // central vertices 
   List  P = newList(); // peripheral vertices 
   List  E = newList(); // eccentricities 
   Graph G = NULL;

   // Build graph G 
   G = newGraph(n);
   //create a small directed Graph
   addArc(G,1,2);
   addArc(G,1,3);
   addArc(G,2,4);
   addArc(G,3,6);
   addArc(G,3,5);
   addArc(G,4,8);
   addArc(G,4,2);
    
   // //test the functions of the ADT
   printf("The order is %i\n",getOrder(G));
   printf("The size is %i\n",getSize(G));
   BFS(G,1);
   printf("The source is %i\n",getSource(G));
   printf("The parent of 5 is %i\n",getParent(G,5));
   printf("The distance from source to 8 is %i\n",getDist(G,8));
   printf("path from source to 6 is: ");
   getPath(L,G,6);
   printList(stdout,L);
   clear(L);
   printf("path from source to 7 is: ");
   getPath(L,G,7);
   printList(stdout,L);
   makeNull(G);
   
   //Test Client from the examples
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
   freeList(&L);
   freeList(&C);
   freeList(&P);
   freeList(&E);
   freeGraph(&G);

   return(0);
}

