This program uses a Graph ADT and the Breadth First Search (BFS) algorithm to find shortest paths (paths with the fewest edges) between pairs of vertices.

## Details
FindPath.c is a client that prints a list of connected vertices for each vertex and finds the shortest paths between 2 vertices.
FindPath takes 2 command line arguments: % FindPath input_file output_file

in1, in2, out1, and out 2 are example input files and their respective program outputs. Input files begin with the number of vertices, followed by the edges (represented by a pair of end vertices separated by a space), and is finished with a "0 0" dummy line. An optional second part involves a beginning and an end vertex to perform BFS on, and also ends with a "0 0" dummy line.

Makefile has a make command that creates an executable jar file named FindPath & includes a clean utility.

List.c is a List ADT that is a doubly linked list. Each node of the list contains an int (the data) and 2 Node references. The List class contains three specific Nodes (front, back, cursor), the length of the list, and the index of the cursor. When the cursor is undefined, its index is -1.

List.h is a header file for the List ADT in List.c.

Graph.c is a Graph ADT for the FindPath.c client that utilizes an adjacency list representation.

Graph.h is a header file for the Graph ADT in Graph.c.

GraphTest.c is a test client for the Graph ADT while it was under construction.