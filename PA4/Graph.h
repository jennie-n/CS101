//-----------------------------------------------------------------------------
// Jennie Nguyen
// jnguy189
// cmps101
// 28 May 2019
// Graph.h
// Header file for Graph ADT
//-----------------------------------------------------------------------------

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#include <stdio.h>
#include "List.h"
#define INF -1
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

// getSource()
// returns the source vertex most recently used in BFS(), or NIL if BFS() hasn't yet been called
int getSource(Graph G);

// getParent()
// returns the parent of vertex u in the BFS tree created by BFS(), or NIL if BFS() hasn't yet been called
// Pre: 1<=u<=getOrder(G)
int getParent(Graph G, int u);

// getDist()
// returns the distance from the most recent BFS source to vertex u, or INF if BFS() hasn't yet been called
// Pre: 1<=u<=getOrder(G)
int getDist(Graph G, int u);

// getPath()
// appends to L the vertices of a shortest path in G from source to u, or NIL if no such path exists
// Pre: 1<=u<=getOrder(G) and getSource(G)!=NIL, so BFS() must be called before getPath()
void getPath(List L, Graph G, int u);

// Manipulation procedures -----------------------------------------------------------

// makeNull()
// deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G);

// addEdge()
// inserts a new edge joining u to v
// AKA u is added to adjacency list of v, and v to the adjacency list of u
// Pre: 1<=u<=getOrder(G) and 1<=v<=getOrder(G)
void addEdge(Graph G, int u, int v);

// addArc()
// inserts a new directed edge from u to v
// AKA v is added to the adjacency list of u, but NOT u to the adjacency list of v
// Pre: 1<=u<=getOrder(G) and 1<=v<=getOrder(G)
void addArc(Graph G, int u, int v);

// BFS()
// runs the BFS algorithm on G with source s, setting the color, distance, parent, and source fields of G accordingly
void BFS(Graph G, int s);

// Other Operations -----------------------------------------------------------

// printGraph()
// prints the adjacency list representation of G to file out
void printGraph(FILE* out, Graph G);

#endif