This program implements the Depth First Search (DFS) algorithm and a Graph to find the strongly connected components (SCC) of a directed graph. 
A component is a SCC if every vertex in graph X is reachable from every other vertex in X. In other words, for every pair of vertices u and v, vertex u is reachable from v, and vertex v is reachable from u.

## Details
FindComponents.c is a client that utilizes the Graph ADT and finds the strongly connected components of a graph G.
FindComponents takes 2 command line arguments: % FindComponents input_file output_file

Makefile has a make command that creates an executable jar file named FindComponents & includes a clean utility.

List.c is a List ADT that is a doubly linked list. Each node of the list contains an int (the data) and 2 Node references. The List class contains three specific Nodes (front, back, cursor), the length of the list, and the index of the cursor. When the cursor is undefined, its index is -1.

List.h is a header file for the List ADT in List.c.

Graph.c is a Graph ADT for the FindComponents.c client that utilizes an adjacency list representation. Many aspects of Graph.c are copied from the Graph.c module used in my pa4.

Graph.h is a header file for the Graph ADT in Graph.c.

GraphTest.c is a test client for the Graph ADT while it was under construction.