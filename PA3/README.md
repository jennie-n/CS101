This program is a calculator for performing matrix operations that exploits the (expected) sparseness of its matrix inputs.
It will read an input file with matrices A and B, build the Array of Lists representation of these matrices, then calculate and print the following matrices to the output file: A, B, (1.5)A, A + B, A + A, B − A, A − A, A^T, AB, and B^2.

## Details
in1, in2, out1, and out2 are example input files and their respective program output.

Sparse.java is a Matrix ADT client that takes in 2 arguments (the input and output files) and prints the following matrices to the output file: A, B, (1.5)A, A + B, A + A, B − A, A − A, A^T, AB and B^2.
Sparse takes 2 command line arguments: % Sparse input_file output_file

Makefile has a make command that creates an executable binary file named Sparse & includes a clean utility.

Matrix.java is a Matrix ADT that is a 1-dimensional array of lists. Each entry of a matrix contains an int (the index/column of the matrix) and a double (the value). The Matrix class contains its size, the number of non-zero entries, and at least 1 row.

List.java is a List ADT that is a doubly linked list. Each node of the list contains an Object (the data) and 2 Node references. The List class contains three specific Nodes (front, back, cursor), the length of the list, and the index of the cursor. When the cursor is undefined, its index is -1.

ListTest.java and MatrixTest.java are test clients for the List and Matrix ADTs, respectively, while they were under construction.