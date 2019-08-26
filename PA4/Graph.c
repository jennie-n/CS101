//---------------------------------------------------------------------------
// Jennie Nguyen
// jnguy189
// cmps101
// 28 May 2019
// Graph.c
// Graph ADT for the FindPath.c client
//---------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"

#define WHITE 0000000
#define GRAY 7777777
#define BLACK 9999999

// structs --------------------------------------------------------------------

// GraphObj type
typedef struct GraphObj{
   List* adj;
   int* color;
   int* parent;
   int* distance;
   int order; // the number of vertices
   int size;  // the number of edges
   int source;// vertex most recently used as source for BFS
} GraphObj;

// Constructors-Destructors -----------------------------------------------------------

// newGraph()
// Returns reference to new Graph object with n vertices and no edges
Graph newGraph(int n){
   Graph G = malloc(sizeof(GraphObj));
   assert(G!=NULL);
   G->adj = calloc(n+1, sizeof(List));
   G->color = calloc(n+1, sizeof(int));
   G->parent = calloc(n+1, sizeof(int));
   G->distance = calloc(n+1, sizeof(int));
   G->order = n;
   G->size = 0;
   G->source = NIL;

   // set all vertices to be white, with no parent, and infinite distance from the source
   for(int k=1; k<=n; k++){
      G->adj[k] = newList();
      G->color[k] = WHITE;
      G->parent[k] = NIL;
      G->distance[k] = INF;
   }

   return(G);
}

// freeGraph()
// frees all dynamic memory associated with Graph *pG and sets *pG to NULL
void freeGraph(Graph* pG){
   if(pG!=NULL && *pG!=NULL) { 
   	  Graph G = *pG;

         for(int k=1; k<=getOrder(G); k++){
            freeList(&(G->adj[k]));
         }

         free(G->adj);
         free(G->color);
         free(G->parent);
         free(G->distance);
         free(*pG);
         *pG = NULL;
   }
}

// Access functions -----------------------------------------------------------

// getOrder()
// returns the order of G
int getOrder(Graph G){
   if( G==NULL ){
      printf("Graph Error: calling getOrder() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   return(G->order);
}

// getSize()
// returns the size of G
int getSize(Graph G){
   if( G==NULL ){
      printf("Graph Error: calling getSize() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   return(G->size);
}

// getSource()
// returns the source vertex most recently used in BFS(), or NIL if BFS() hasn't yet been called
int getSource(Graph G){
   if( G==NULL ){
      printf("Graph Error: calling getSource() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   return(G->source);
}

// getParent()
// returns the parent of vertex u in the BFS tree created by BFS(), or NIL if BFS() hasn't yet been called
// Pre: 1<=u<=getOrder(G)
int getParent(Graph G, int u){
   if( G==NULL ){
      printf("Graph Error: calling getParent() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( u<1 || u>getOrder(G) ){
      printf("Graph Error: vertex u is not a part of graph G\n");
      exit(EXIT_FAILURE);
   }
   return(G->parent[u]);
}

// getDist()
// returns the distance from the most recent BFS source to vertex u, or INF if BFS() hasn't yet been called
// Pre: 1<=u<=getOrder(G)
int getDist(Graph G, int u){
   if( G==NULL ){
      printf("Graph Error: calling getDist() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( u<1 || u>getOrder(G) ){
      printf("Graph Error: vertex u is not a part of graph G\n");
      exit(EXIT_FAILURE);
   }
   return(G->distance[u]);
}

// getPath()
// appends to L the vertices of a shortest path in G from source to u, or NIL if no such path exists
// Pre: 1<=u<=getOrder(G) and getSource(G)!=NIL, so BFS() must be called before getPath()
void getPath(List L, Graph G, int u){
   if( L==NULL ){
      printf("List Error: calling getPath() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( G==NULL ){
      printf("Graph Error: calling getPath() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( u<1 || u>getOrder(G) ){
      printf("Graph Error: vertex u is not a part of graph G\n");
      exit(EXIT_FAILURE);
   }
   if( getSource(G)==NIL ){
      printf("Graph Error: BFS() must be called before getPath()\n");
      exit(EXIT_FAILURE);
   }

   if( G->source==u ){ // if u is the source
      append(L, u); // add it to the beginning of the path/List
   } else if( G->parent[u]==NIL ){
      append(L, NIL);
   } else { // if G->parent[u]!=NIL
      getPath(L, G, G->parent[u]);
      append(L, u);
   }
}

// Manipulation procedures -----------------------------------------------------------

// makeNull()
// deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G){
   if( G==NULL ){
      printf("Graph Error: calling makeNull() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   for(int k=1; k<=getOrder(G); k++){
      clear(G->adj[k]);
   }
   G->size = 0;
}

// insert()
// helper function for addEdge()
void insert(List L, int toBeInserted){
   if( L==NULL ){
      printf("List Error: calling insert() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   moveFront(L);
   while( index(L)!=-1 ){
      int compare = get(L);
      if(toBeInserted > compare){
         moveNext(L);
      } else { // if toBeInserted<=compare
         insertBefore(L, toBeInserted);
         break;
      }
   }
   // break lands here
   if( index(L)==-1 ){ // if cursor fell off the list
      append(L, toBeInserted);
   }
}

// addEdge()
// inserts a new edge joining u to v
// AKA u is added to adjacency list of v, and v to the adjacency list of u
// Pre: 1<=u<=getOrder(G) and 1<=v<=getOrder(G)
void addEdge(Graph G, int u, int v){
   if( G==NULL ){
      printf("Graph Error: calling addEdge() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( u<1 || u>getOrder(G) ){
      printf("Graph Error: vertex u is not a part of graph G\n");
      exit(EXIT_FAILURE);
   }
   if( v<1 || v>getOrder(G) ){
      printf("Graph Error: vertex v is not a part of graph G\n");
      exit(EXIT_FAILURE);
   }

   insert(G->adj[u], v);
   insert(G->adj[v], u);
   G->size++; // added one edge
}

// addArc()
// inserts a new directed edge from u to v
// AKA v is added to the adjacency list of u, but NOT u to the adjacency list of v
// Pre: 1<=u<=getOrder(G) and 1<=v<=getOrder(G)
void addArc(Graph G, int u, int v){
   if( G==NULL ){
      printf("Graph Error: calling addArc() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( u<1 || u>getOrder(G) ){
      printf("Graph Error: vertex u is not a part of graph G\n");
      exit(EXIT_FAILURE);
   }
   if( v<1 || v>getOrder(G) ){
      printf("Graph Error: vertex v is not a part of graph G\n");
      exit(EXIT_FAILURE);
   }

   insert(G->adj[u], v);
   G->size++; // added one edge
}

// BFS()
// runs the BFS algorithm on G with source s, setting the color, distance, parent, and source fields of G accordingly
void BFS(Graph G, int s){
   if( G==NULL ){
      printf("Graph Error: calling BFS() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( s<1 || s>getOrder(G) ){
      printf("Graph Error: vertex s is not a part of graph G\n");
      exit(EXIT_FAILURE);
   }

   int x, y;
   G->source = s;

   // initialize BFS chart
   for(int k=1; k<=getOrder(G); k++){
      G->color[k] = WHITE;
      G->parent[k] = NIL;
      G->distance[k] = INF;
   }
   G->color[s] = GRAY; // discover source s
   G->distance[s] = 0;
   G->parent[s] = NIL;

   List L = newList(); // construct a new empty List
   append(L, s);
   while( length(L)!=0 ){ // while L is not empty
      x = front(L);
      deleteFront(L);
      moveFront(G->adj[x]);
      while( index(G->adj[x])!=-1 ){
         y = get(G->adj[x]);
         if( G->color[y]==WHITE ){ // if y is undiscovered
            G->color[y] = GRAY;    // discover y
            G->distance[y] = G->distance[x] + 1;
            G->parent[y] = x;
            append(L, y);
         }
         moveNext(G->adj[x]);
      }
      G->color[x] = BLACK; // finish x
   }
   freeList(&L);
}

// Other Operations -----------------------------------------------------------

// printGraph()
// prints the adjacency list representation of G to file out
void printGraph(FILE* out, Graph G){
   if( G==NULL ){
      printf("Graph Error: calling printGraph() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }

   for(int k=1; k<=getOrder(G); k++){
      fprintf(out, "%d: ", k);
      printList(out, G->adj[k]);
      fprintf(out, "\n");
   }
}