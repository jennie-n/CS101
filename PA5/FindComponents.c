//---------------------------------------------------------------------------
// Jennie Nguyen
// jnguy189
// cmps101
// 6 June 2019
// FindComponents.c
// client that utilizes the Graph ADT and finds the strongly connected
// components of a graph G
//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define MAX_LEN 256

int main(int argc, char* argv[]){
    /* check command line for correct number of arguments */
    if( argc != 3 ){
        printf("Usage: FindComponents <input file> <output file>\n");
        exit(EXIT_FAILURE);
    }

    FILE* in; // file handle for input
    FILE* out; // file handle for output
    char c[MAX_LEN];

    // open files for reading
    in = fopen(argv[1], "r");
    if( in==NULL ){
        printf("Unable to read from input file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    out = fopen(argv[2], "w");
    if( out==NULL ){
        printf("Unable to write to file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    fgets(c, MAX_LEN, in); // get the first int from input file: number of vertices in the graph
    int sizeGraph = 0;
    sscanf(c, "%d", &sizeGraph);
    List S = newList();
    for(int k=1; k<=sizeGraph; k++){
        append(S, k);
    }

    // assemble a graph G using newGraph() and addArc()
    Graph G = newGraph(sizeGraph);

    int x, y;
    while( fgets(c, MAX_LEN, in)!=NULL ){
    	x = 0;
    	y = 0;
    	sscanf(c, "%d %d", &x, &y);
    	if(x==0 && y==0){
    		break;
    	}
    	addArc(G, x, y);
    }
    // break lands here

    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G); // prints adjacency list representation of graph

    // run DFS on G and its transpose
    DFS(G, S);
    Graph transpos = transpose(G);
    int nSCC = 0;
    DFS(transpos, S);
    moveFront(S);

    while( index(S)>=0 ){
        if(getParent(transpos, get(S))==NIL){
            nSCC++;
        }
        moveNext(S);
    }

    // determine strong components of G
    List lSCC[nSCC]; // list of strongly connected components
    for(int t=0; t<nSCC; t++){
        lSCC[t] = newList();
    }

    moveFront(S);
    int j = nSCC;
    while( index(S)>=0 ){
        if( getParent(transpos, get(S))==NIL ){
            j--;
        }
        if( j==nSCC ){
            break;
        }
        append(lSCC[j], get(S));
        moveNext(S);
    }
    // break lands here

    // print the strong components of G in topologically sorted order
    fprintf(out, "\nG contains %d strongly connected components:", nSCC);
    for(int a=0; a<nSCC; a++){
      fprintf(out, "\nComponent %d: ", (a + 1));
      printList(out, lSCC[a]);
      freeList(&(lSCC[a]));
    }
    fprintf(out, "\n");

	freeGraph(&transpos);
    freeGraph(&G);
    freeList(&S);

    // close input and output files
    fclose(in);
    fclose(out);

    return(EXIT_SUCCESS);
}