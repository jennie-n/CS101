//-----------------------------------------------------------------------------
//  Jennie Nguyen
//  jnguy189
//  cmps101
//  6 May 2019
//  MatrixTest.java
//
//  A test client for the Matrix ADT while it was under construction
//-----------------------------------------------------------------------------

public class MatrixTest{
    public static void main(String[] args){

        Matrix A = new Matrix(3);
        A.changeEntry(1, 1, 1);
        A.changeEntry(1, 2, 2);
        A.changeEntry(1, 3, 3);
        A.changeEntry(2, 1, 4);
        A.changeEntry(2, 2, 5);
        A.changeEntry(2, 3, 6);
        A.changeEntry(3, 1, 7);
        A.changeEntry(3, 2, 8);
        A.changeEntry(3, 3, 9);
        System.out.println("Matrix A:");
        System.out.println(A);
        Matrix B = new Matrix(3);
        B.changeEntry(1, 1, 1);
        B.changeEntry(1, 2, 0);
        B.changeEntry(1, 3, 1);
        B.changeEntry(2, 1, 0);
        B.changeEntry(2, 2, 1);
        B.changeEntry(2, 3, 0);
        B.changeEntry(3, 1, 1);
        B.changeEntry(3, 2, 1);
        B.changeEntry(3, 3, 1);
        System.out.println("Matrix B:");
        System.out.println(B);
        Matrix C = A.copy();
        System.out.println("Matrix A copy:");
        System.out.println(C);
        Matrix D = new Matrix(3);
        System.out.println("Matrix D:");
        System.out.println(D);
        Matrix E = D.copy();
        System.out.println("Matrix E:");
        System.out.println(E);
        B.makeZero();
        System.out.println("Matrix B's makeZero() test:");
        System.out.println(B);
    }
}