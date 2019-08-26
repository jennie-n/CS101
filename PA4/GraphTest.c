//---------------------------------------------------------------------------
// Jennie Nguyen
// jnguy189
// cmps101
// 28 May 2019
// GraphTest.c
// Test client for the Graph ADT while it was under construction
//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char* argv[]){
   int size = 4;
   Graph G = newGraph(size);

   printGraph(stdout, G); // print empty graph

   printf("Order: %d\n", getOrder(G)); // 5
   printf("Size: %d\n", getSize(G)); // 0
   printf("Source: %d\n", getSource(G)); // NIL aka 0
   printf("Parent of 5: %d\n", getParent(G, 5)); // NIL aka 0
   printf("Distance to source: %d\n\n", getDist(G, 1)); // INF aka -1

   addEdge(G, 1, 2);
   addEdge(G, 2, 3);
   addEdge(G, 1, 3);

   freeGraph(&G);

   printGraph(stdout, G); // print empty graph

   printf("Order: %d\n", getOrder(G)); // 5
   printf("Size: %d\n", getSize(G)); // 3
   printf("Source: %d\n", getSource(G)); // NIL aka 0
   printf("Parent of 1: %d\n", getParent(G, 1)); // NIL aka 0
   printf("Distance to source: %d\n\n", getDist(G, 1)); // INF aka -1

   addArc(G, 3, 4);
   addArc(G, 4, 3);
   printf("Size: %d\n", getSize(G)); // 5

   BFS(G, 1);
   printf("Distance between 1-4: %d\n", getDist(G, 4)); // 2
   printf("Parent of 3: %d\n", getParent(G, 3)); // 1

   List L = newList();					
   printf("A shortest 1-4 path is: ");
   getPath(L, G, 4);
   printList(stdout, L); // 1 3 4
   printf("\n");
   freeList(&L);

   makeNull(G);				// print empty graph
   printGraph(stdout, G);
   printf("Size: %d\n", getSize(G)); // 0

   return(0);
}
