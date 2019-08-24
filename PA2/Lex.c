
//---------------------------------------------------------------------------
// Jennie Nguyen
// jnguy189
// cmps12b
// 22 April 2019
// List.c
// A client module that takes 2 command line arguments (the input and output files, respectively)
// and implements the List ADT to sort the elements of an input array indirectly. 
//---------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"List.h"

int main(int argc, char* argv[]){
    /* check command line for correct number of arguments */
    if( argc != 3 ){
        printf("Usage: Lex <input file> <output file>\n");
        exit(EXIT_FAILURE);
    }

    FILE* count;
    FILE* in; /* file handle for input */
    FILE* out; /* file handle for output */
    char c;

    // open files for reading
    count = fopen(argv[1], "r");
    if( count==NULL ){
        printf("Unable to read from file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    in = fopen(argv[1], "r");

    // count the number of lines n in the input file
    int n=0;
    c = getc(count); // get a character from the input file
    while(c != EOF){
        if(c == '\n'){
            n++;
        }
        c = getc(count); // move on to the next character in the input file
    }

    // create a "String" array of length n
    char allInputs [n][1000];
    char line [1000];
    int i=0;
    // read in files and store them in allInputs
    while( fgets(line, sizeof line, in) != NULL ){
        strcpy(allInputs[i], line);
        i++;
    } // i should be n-1 at this point

    // Create a List whose elements are the indices of the above String array.
    // These indices should be arranged in an order that effectively sorts the array.
    List L = newList();
    int j=0;
    prepend(L, j);
    j++;

    for(int k=1; k<n; k++){
        moveBack(L); // cursor is at the back of the List

        while( index(L)>=0 ){
            if( strcmp(allInputs[k], allInputs[get(L)])<0 ){ // while the string at the array index to be added is alphabetically before the element at the cursor
                movePrev(L);
            } else {
                break;
            }
        } // break lands here

        if( index(L) == -1 ){
            prepend(L, k);
        } else if ( index(L)==0 && strcmp(allInputs[k], allInputs[get(L)])<0 ){ // if index is 0 AND array element to be added is alphabetically before the front, then we should add to the front of the list
            prepend(L, k);
        } else {
            insertAfter(L, k);
        }
    }

    // open output file for writing
    out = fopen(argv[2], "w");
    if( out==NULL ){
        printf("Unable to write to file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    for(moveFront(L); index(L)>=0; moveNext(L)){ // move cursor through List
        fprintf(out, "%s", allInputs[get(L)]);
    }


    freeList(&L);
    // close input and output files
    fclose(count);
    fclose(in);
    fclose(out);

    return(EXIT_SUCCESS);
}