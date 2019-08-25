//-----------------------------------------------------------------------------
//  Jennie Nguyen
//  jnguy189
//  cmps101
//  6 May 2019
//  ListTest.java
//
//  A test client for the List ADT while it was under construction
//-----------------------------------------------------------------------------

public class ListTest{
   public static void main(String[] args){
      List K = new List();
      List J = new List();
      
      for(int kj=1; kj<=20; kj++){
         K.append(kj);
         J.prepend(kj);
      }
      System.out.println(K); // 1 through 20
      System.out.println(J); // 20 through 1
      
      K.append("blah"); // 1 through 20, blah
      J.append(7.7); // 20 through 1, 7.7

      for(K.moveFront(); K.index()>=0; K.moveNext()){
         System.out.print(K.get()+" "); // prints 1 through 20, blah
      }
      System.out.println();
      for(J.moveBack(); J.index()>=0; J.movePrev()){
         System.out.print(J.get()+" "); // prints 7.7, 1 through 20
      }
      System.out.println();
      
      List H = new List();
      System.out.println(K.equals(J)); // false
      System.out.println(J.equals(H)); // false
      System.out.println(H.equals(K)); // false
      
      K.moveFront();
      for(int i=0; i<5; i++) K.moveNext(); // at index 5
      K.insertBefore(-1);                  // at index 6
      for(int i=0; i<9; i++) K.moveNext(); // at index 15
      K.insertAfter(-2);                   // at index 16
      for(int i=0; i<5; i++) K.movePrev(); // at index 10
      K.delete();
      System.out.println(K);
      System.out.println(K.length());
      K.clear();
      System.out.println(K.length());
   }
}