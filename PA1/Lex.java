
//---------------------------------------------------------------------------
// Jennie Nguyen
// jnguy189
// cmps101
// 12 April 2019
// Lex.java
// A client module that takes 2 command line arguments (the input and output files, respectively)
// and implements the List ADT to sort the elements of an input array indirectly. 
//---------------------------------------------------------------------------

import java.io.*;
import java.util.Scanner;

public class Lex{

    public static void main(String[] args) throws IOException{

        // check number of command line arguments is 2
        if(args.length != 2){
            System.err.println("Usage: Lex <input file> <output file>");
            System.exit(1);
        }

    	// open files
        Scanner count = new Scanner(new File(args[0]));
        Scanner in = new Scanner(new File(args[0]));

        // count the number of lines n in the input file named by args[0]
        int n=0;
        while(count.hasNextLine()){
            n++;
            count.nextLine();
        }

        // Create a String array of length n
        String[] allInputs = new String[n];
        int addHere=0;
        String line;

        // Read in the lines of the file as Strings, placing them into the array
        while(in.hasNextLine()){
            line = in.nextLine().trim() + " "; // trim leading and trailing spaces, then add one trailing space so split works on blank lines
            allInputs[addHere] = line;
            addHere++;
        }

        // Create a List whose elements are the indices of the above String array.
        // These indices should be arranged in an order that effectively sorts the array.
        List L = new List();
        int index=0; // index is the array index that is about to be added to the list
        L.prepend(index); // insert 1st array index into array
        int indexThatWasJustAdded = 0;
        index++; // index is now 1


        for(int i=1; i<allInputs.length; i++){
            L.moveBack(); // cursor is at the back of the List

            while(L.index()>=0){
                if( allInputs[i].compareTo( allInputs[L.get()])<0){ // while the string at the array index to be added is alphabetically before the element at the cursor
                    L.movePrev(); // move cursor 1 step towards front of list
                } else {
                    break;
                }
            } // break lands here


            if(L.index() == -1){ // if index is -1, then cursor fell off front of list and we should add to the front of the list
                L.prepend(i);
            } else if (L.index()==0 && allInputs[i].compareTo(allInputs[L.get()])<0){ // if index is 0 AND array element to be added is alphabetically before the front, then we should add to the front of the list
                L.prepend(i);
            } else {
                L.insertAfter(i);
            }

        }

        // open files for writing
        PrintWriter output = new PrintWriter(new FileWriter(args[1]));

        for(L.moveFront(); L.index()>=0; L.moveNext()){ // move cursor through List
            output.println( allInputs[L.get()] );
        }

        // close input and output files
        count.close();
      	in.close();
        output.close();

    }
}
