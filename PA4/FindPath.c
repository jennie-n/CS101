//---------------------------------------------------------------------------
// Jennie Nguyen
// jnguy189
// cmps101
// 28 May 2019
// FindPath.c
// client that utilizes Graph ADT and finds the shortest paths (paths with the
// fewest edges) between 2 vertices
//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define MAX_LEN 256

int main(int argc, char* argv[]){
    /* check command line for correct number of arguments */
    if( argc != 3 ){
        printf("Usage: FindPath <input file> <output file>\n");
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
    Graph G = newGraph(sizeGraph);

    int x, y;
    while( fgets(c, MAX_LEN, in)!=NULL ){
    	x = 0;
    	y = 0;
    	sscanf(c, "%d %d", &x, &y);
    	if(x==0 && y==0){
    		break;
    	}
    	addEdge(G, x, y);
    }
    // break lands here
    printGraph(out, G); // prints adjacency list representation of graph

    int destination, source, distance;
    List path = newList();
	while( fgets(c, MAX_LEN, in)!=NULL ){
		destination = 0;
		source = 0;
		sscanf(c, "%d %d", &destination, &source);
		if(destination==0 && source==0){
			break;
		}

		BFS(G, destination);

		fprintf(out, "\nThe distance from %d to %d is ", destination, source);
		distance = getDist(G, source); // distance from destination to source
		if( distance==INF ){
			fprintf(out, "infinity\n");
		} else {
			fprintf(out, "%d\n", distance);
		}
		
		clear(path);
		getPath(path, G, source);
		if( front(path)==NIL ){
			fprintf(out, "No %d-%d path exists\n", destination, source);
		} else {
			fprintf(out, "A shortest %d-%d path is: ", destination, source);
			printList(out, path);
			fprintf(out, "\n");
		}
	} 
	// break lands here
	freeList(&path);
    freeGraph(&G);

    // close input and output files
    fclose(in);
    fclose(out);

    return(EXIT_SUCCESS);
}