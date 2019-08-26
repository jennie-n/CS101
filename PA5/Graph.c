//---------------------------------------------------------------------------
// Jennie Nguyen
// jnguy189
// cmps101
// 6 June 2019
// Graph.c
// Graph ADT for the FindComponents.c client
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
   int* discover;
   int* finish;
   int order; // the number of vertices
   int size;  // the number of edges
   int time;  // needed?
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
   G->discover = calloc(n+1, sizeof(int));
   G->finish = calloc(n+1, sizeof(int));
   G->order = n;
   G->size = 0;
   G->time = UNDEF;

   // set all vertices to be white, with no parent, and undefined discover and finish times
   for(int k=1; k<=n; k++){
      G->adj[k] = newList();
      G->color[k] = WHITE;
      G->parent[k] = NIL;
      G->discover[k] = UNDEF;
      G->finish[k] = UNDEF;
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
         free(G->discover);
         free(G->finish);
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

// getParent()
// returns the parent of vertex u, or NIL if DFS() hasn't yet been called
// Pre: 1<=u<=n=getOrder(G)
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

// getDiscover()
// returns the discover time of vertex u, or UNDEF if DFS() hasn't yet been called
// Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u){
   if( G==NULL ){
      printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( u<1 || u>getOrder(G) ){
      printf("Graph Error: vertex u is not a part of graph G\n");
      exit(EXIT_FAILURE);
   }
   return(G->discover[u]);
}

// getFinish()
// returns the discover time of vertex u, or UNDEF if DFS() hasn't yet been called
// Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u){
   if( G==NULL ){
      printf("Graph Error: calling getFinish() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( u<1 || u>getOrder(G) ){
      printf("Graph Error: vertex u is not a part of graph G\n");
      exit(EXIT_FAILURE);
   }
   return(G->finish[u]);
}

// Manipulation procedures -----------------------------------------------------------

// insert()
// helper function for addArc() and addEdge()
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

// addEdge()
// inserts a new edge joining u to v
// AKA u is added to adjacency list of v, and v to the adjacency list of u
// Pre: 1<=u<=n=getOrder(G) and 1<=v<=n=getOrder(G)
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

// Visit()
// helper function for DFS()
void Visit(Graph G, List S, int x){
   if( G==NULL ){
      printf("Graph Error: calling Visit() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( S==NULL ){
      printf("List Error: calling Visit() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   G->time++;
   G->discover[x] = G->time; // discover x
   G->color[x] = GRAY;
   moveFront(G->adj[x]);
   int k;
   while( index(G->adj[x]) >= 0 ){
      k = get(G->adj[x]);
      if(G->color[k]==WHITE){
         G->parent[k] = x;
         Visit(G, S, k);
      }
      moveNext(G->adj[x]);
   }
   G->color[x] = BLACK;
   G->time++;
   G->finish[x] = G->time; // finish x
   prepend(S, x);
}

// DFS()
// runs the DFS algorithm on G
// Pre: (i) length(S) == n, and (ii) S contains some permutation of the integers {1, 2, ... , n} where n = getOrder(G)
void DFS(Graph G, List S){
   if( G==NULL ){
      printf("Graph Error: calling DFS() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   // check for first precondition
   if(length(S) != getOrder(G)){
      printf("DFS() Error: List S is not the same size as Graph G");
      exit(EXIT_FAILURE);
   }

   int k;
   // initialize DFS chart
   for(k=1; k<=getOrder(G); k++){
      G->color[k] = WHITE;
      G->parent[k] = NIL;
      G->discover[k] = UNDEF;
      G->finish[k] = UNDEF;
   }
   G->time = 0;
   
   moveFront(S);
   while( index(S)>=0 ){
      k = get(S);
      if(G->color[k]==WHITE){
         Visit(G, S, k);
      }
      moveNext(S);
   }
   
   for(int size=length(S)/2; size>0; size--){
      deleteBack(S);
   }
}

// Other Operations -----------------------------------------------------------

// transpose()
// returns a reference to a new graph representing the transpose of G
Graph transpose(Graph G){
   if( G==NULL ){
      printf("Graph Error: calling transpose() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }

   Graph answer = newGraph(getOrder(G));
   for(int k=1; k<=getOrder(G); k++){
      moveFront(G->adj[k]);
      while( index(G->adj[k]) >= 0 ){
         addArc(answer, get(G->adj[k]), k);
         moveNext(G->adj[k]);
      }
   }
   return answer;
}

// copyGraph()
// returns a reference to a new graph which is a copy of G
Graph copyGraph(Graph G){
   if( G==NULL ){
      printf("Graph Error: calling copyGraph() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }

   Graph answer = newGraph(getOrder(G));
   for(int k=1; k<=getOrder(G); k++){
      moveFront(G->adj[k]);
      while( index(G->adj[k]) >= 0 ){
         addArc(answer, k, get(G->adj[k]));
         moveNext(G->adj[k]);
      }
   }
   return answer;
}

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