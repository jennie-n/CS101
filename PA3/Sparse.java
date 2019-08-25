//-----------------------------------------------------------------------------
//  Jennie Nguyen
//  jnguy189
//  cmps101
//  6 May 2019
//  Sparse.java
//
//  Matrix ADT client that takes in 2 arguments (the input and output files) and
//  prints the following matrices to the output file: A, B, (1.5)A, A + B, A + A,
//  B − A, A − A, A^T, AB and B^2.
//-----------------------------------------------------------------------------

import java.io.*;
import java.util.Scanner;

public class Sparse{
	public static void main(String[] args) throws IOException{
		if(args.length != 2){
            System.err.println("Usage: Sparse <input file> <output file>");
            System.exit(1);
		}

		// open files
        Scanner in = new Scanner(new File(args[0]));
        PrintWriter out = new PrintWriter(new FileWriter(args[1]));

        int size = in.nextInt();
        int nnzOfA = in.nextInt();
        int nnzOfB = in.nextInt();

        Matrix A = new Matrix(size);
        // fill matrix A
        for(int a=1; a<=nnzOfA; a++){
        	A.changeEntry(in.nextInt(), in.nextInt(), in.nextDouble());
        }

        Matrix B = new Matrix(size);
        // fill matrix B
        for(int b=1; b<=nnzOfB; b++){
        	B.changeEntry(in.nextInt(), in.nextInt(), in.nextDouble());
        }

        out.println("A has " + nnzOfA + " non-zero entries:");
        out.println(A);

        out.println("B has " + nnzOfB + " non-zero entries:");
        out.println(B);

        out.println("(1.5)*A =");
        out.println(A.scalarMult(1.5));

        out.println("A+B =");
        out.println(A.add(B));

        out.println("A+A =");
        out.println(A.add(A));

        out.println("B-A =");
        out.println(B.sub(A));

		out.println("A-A =");
        out.println(A.sub(A));        

        out.println("Transpose(A) =");
        out.println(A.transpose());

        out.println("A*B =");
        out.println(A.mult(B));


        out.println("B*B =");
        out.println(B.mult(B));


        // close files
        in.close();
        out.close();
	}
}