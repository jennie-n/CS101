This program uses an Integer List ADT to alphabetize the lines of an input file and outputs the alphabetized version. Same functionality as PA2, but written in Java.

## Details
in1 and out1 is an example input file and its program output.

Lex.java is a client module that takes 2 command line arguments (the input and output files, respectively) and implements the List ADT to sort the elements of an input array indirectly.
Lex takes 2 command line arguments: % Lex input_file output_file

Makefile has a make command that compiles all .java files in the current directory, creates an executable jar file named Lex, and includes a clean utility that removes Lex and any associated .class files.

List.java is a List ADT that is a doubly linked list. Each node of the list contains an int (the data) and 2 Node references. The List class contains three specific Nodes (front, back, cursor), the length of the list, and the index of the cursor. When the cursor is undefined, its index is -1.

ListClient.java is a test client for the List ADT & was provided to us.