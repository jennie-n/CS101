This program uses an Integer List ADT to alphabetize the lines of an input file and outputs the alphabetized version. Same functionality as PA1, but written in C.

## Details
in1 and out1 is an example input file and its program output.

Lex.c is a client module that takes 2 command line arguments (the input and output files, respectively) and implements the List ADT to sort (alphabetize) the elements of an input array indirectly.
Lex takes 2 command line arguments: % Lex input_file output_file

Makefile has a make command that creates an executable binary file named Lex & includes a clean utility that removes Lex and any associated .o files.

List.c is a List ADT that is a doubly linked list. Each node of the list contains an int (the data) and 2 Node references. The List class contains three specific Nodes (front, back, cursor), the length of the list, and the index of the cursor. When the cursor is undefined, its index is -1.

List.h is a header file for the List ADT in List.c.

ListClient.c is a test client for the List ADT & was provided to us.