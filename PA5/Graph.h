//-----------------------------------------------------------------------------
// Jennie Nguyen
// jnguy189
// cmps101
// 6 June 2019
// Graph.h
// Header file for Graph ADT
//-----------------------------------------------------------------------------

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#include <stdio.h>
#include "List.h"
#define UNDEF -1
#define NIL 0

// Exported type --------------------------------------------------------------
typedef struct GraphObj* Graph;

// Constructors-Destructors -----------------------------------------------------------

// newGraph()
// Returns reference to new Graph object with n vertices and no edges
Graph newGraph(int n);

// freeGraph()
// frees all dynamic memory associated with Graph *pG and sets *pG to NULL
void freeGraph(Graph* pG);

// Access functions -----------------------------------------------------------

// getOrder()
// returns the order of G
int getOrder(Graph G);

// getSize()
// returns the size of G
int getSize(Graph G);

// getParent()
// returns the parent of vertex u, or NIL if DFS() hasn't yet been called
// Pre: 1<=u<=n=getOrder(G)
int getParent(Graph G, int u);

// getDiscover()
// returns the discover time of vertex u, or UNDEF if DFS() hasn't yet been called
// Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u);

// getFinish()
// returns the discover time of vertex u, or UNDEF if DFS() hasn't yet been called
// Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u);

// Manipulation procedures -----------------------------------------------------------

// addArc()
// inserts a new directed edge from u to v
// AKA v is added to the adjacency list of u, but NOT u to the adjacency list of v
// Pre: 1<=u<=n=getOrder(G) and 1<=v<=n=getOrder(G)
void addArc(Graph G, int u, int v);

// addEdge()
// inserts a new edge joining u to v
// AKA u is added to adjacency list of v, and v to the adjacency list of u
// Pre: 1<=u<=n=getOrder(G) and 1<=v<=n=getOrder(G)
void addEdge(Graph G, int u, int v);

// DFS()
// runs the DFS algorithm on G
// Pre: (i) length(S) == n, and (ii) S contains some permutation of the integers {1, 2, ... , n} where n = getOrder(G)
void DFS(Graph G, List S);

// Other Operations -----------------------------------------------------------

// transpose()
// returns a reference to a new graph representing the transpose of G
Graph transpose(Graph G);

// copyGraph()
// returns a reference to a new graph which is a copy of G
Graph copyGraph(Graph G);

// printGraph()
// prints the adjacency list representation of G to file out
void printGraph(FILE* out, Graph G);

#endif