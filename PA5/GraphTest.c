//---------------------------------------------------------------------------
// Jennie Nguyen
// jnguy189
// cmps101
// 6 June 2019
// GraphTest.c
// Test client for the Graph ADT while it was under construction
//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char* argv[]){
   List S = newList();
   Graph G = newGraph(7);
   Graph J = NULL;
   Graph K = NULL;

   fprintf(stdout, "%d\n", getDiscover(G, 7));
   fprintf(stdout, "%d\n", getFinish(G, 7));


   for(int i=1; i<=7; i++) {
      append(S, i);
   }

   addArc(G, 3, 6);
   addArc(G, 3, 7);
   addArc(G, 2, 4);
   addArc(G, 1, 3);
   addArc(G, 1, 5);
   addArc(G, 2, 5);
   addArc(G, 2, 6);
   addArc(G, 3, 2);
   addArc(G, 6, 5);


   printGraph(stdout, G);

   DFS(G, S);
   for(int i=1; i<=7; i++){
      fprintf(stdout, "%d ",  getParent(G, i));
   }
   fprintf(stdout, "\n");

   K = copyGraph(G);
   printGraph(stdout, K); // copy of G
   fprintf(stdout, "\n");

   J = transpose(G);
   printGraph(stdout, J); // transpose of G
   fprintf(stdout, "\n");

   return(0);
}
