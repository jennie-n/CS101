//-----------------------------------------------------------------------------
//  Jennie Nguyen
//  jnguy189
//  cmps101
//  6 May 2019
//  Matrix.java
// 
//  A Matrix ADT that is a 1-dimensional array of lists. Each entry of a matrix
//  contains an int (the index/column of the matrix) and a double (the value).
//  The Matrix class contains its size, the number of non-zero entries, and at
//  least 1 row.
//-----------------------------------------------------------------------------
@SuppressWarnings("overrides")
class Matrix{

   @SuppressWarnings("overrides")
   private class Entry{
      // Fields
      int index;
      double value;
      
      // Constructor
      Entry(int column, double value) {
         index = column;
         this.value = value;
      }
      
      // toString():  overrides Object's toString() method
      public String toString() { 
         return "(" + index + ", " + value + ")"; 
      }
      
      // equals(): overrides Object's equals() method
      public boolean equals(Object x){
         boolean eq = false;
         Entry that;
         if(x instanceof Entry){
            that = (Entry) x;
            eq = (this.value==that.value && this.index==that.index);
         }
         return eq;
      }
   }

   // Fields
   private int size;   // number of rows and columns of this Matrix
   private int nnz;    // number of non-zero entries in this Matrix
   private List[] row;


   // Constructor
   Matrix(int n){ // Makes a new n x n zero Matrix. pre: n>=1
      if( n<1 ){
         throw new RuntimeException(
            "Matrix Error: cannot construct Matrix smaller than 1x1");
      }
      size = n; 
      nnz = 0;
      row = new List[size+1];

      for(int i=1; i<=n; i++){
         row[i] = new List();
      }
   }


   // Access Functions --------------------------------------------------------
   
   // getSize()
   // Returns n, the number of rows and columns of this Matrix
   int getSize(){
      return size;
   }

   // getNNZ()
   // Returns the number of non-zero entries in this Matrix
   int getNNZ(){
      return nnz;
   }

   // equals()
   // overrides Object's equals() method
   public boolean equals(Object x){
      boolean eq  = false;
      Matrix that;

      if(x instanceof Matrix){
         that = (Matrix) x;

         eq = ( (this.size==that.size) && (this.nnz==that.nnz) ); // compare sizes and nnz of this Matrix and x
         
         int i = 1;
         while( eq && i<=this.size ){
            eq = row[i].equals(that.row[i]);
            i++;
         }
      }
      return eq;
   }

   // Helper Functions --------------------------------------------------------

   // dot()
   // calculates the dot product of two Lists
   private double dot(List P, List Q){
      double answer = 0.0;

      Entry currentPEntry, currentQEntry;

      P.moveFront();
      Q.moveFront(); // cursors of P & Q are at the beginning

      if(P.index()==-1 || Q.index()==-1){ // if one/both Lists are all zeros
         return answer;
      } else while(P.index()!=-1 && Q.index()!=-1){ // while neither list's cursor has fallen off the end
         currentPEntry = (Entry) P.get();
         currentQEntry = (Entry) Q.get();
         if(currentPEntry.index == currentQEntry.index){
            answer = answer + (currentPEntry.value * currentQEntry.value);
            P.moveNext();
            Q.moveNext();
         } else if(currentPEntry.index > currentQEntry.index){
            Q.moveNext();
         } else if(currentPEntry.index < currentQEntry.index){
            P.moveNext();
         }
      }

      return answer;
   }

   // addRow()
   // adds 2 rows together
   private List addRow(List T, List Q){
      List answer = new List();

      Entry currentTEntry, currentQEntry;

      T.moveFront();
      Q.moveFront(); // cursors of T & Q are at the beginning
      while(T.index()!=-1 && Q.index()!=-1){
         currentTEntry = (Entry) T.get(); // the entry at T's cursor
         currentQEntry = (Entry) Q.get(); // the entry at Q's cursor

         if(currentTEntry.index == currentQEntry.index){ // if these entries are in the same column, add them
            if(currentTEntry.value + currentQEntry.value == 0){ // if the sum of these entries is 0, don't add the entry to the answer matrix
               T.moveNext();
               Q.moveNext();
            } else { // if the sum of these entries != 0
               Entry currentAnswerEntry = new Entry(currentTEntry.index, currentTEntry.value + currentQEntry.value);
               answer.append(currentAnswerEntry);
               T.moveNext();
               Q.moveNext();
            }
         } else if(currentTEntry.index > currentQEntry.index){
            Entry currentAnswerEntry = new Entry(currentQEntry.index, currentQEntry.value);
            answer.append(currentAnswerEntry); // add entry at Q's cursor to answer matrix
            Q.moveNext();
         } else if(currentTEntry.index < currentQEntry.index){
            Entry currentAnswerEntry = new Entry(currentTEntry.index, currentTEntry.value);
            answer.append(currentAnswerEntry); // add entry at T's cursor to answer matrix
            T.moveNext();
         }
      }
      // at this point, either T and/or Q cursor fell off the row

      while(T.index()!=-1 || Q.index()!=-1){
         if(T.index()!=-1){ // if T's cursor hasn't fallen off yet (aka Q's cursor has fallen off)
            currentTEntry = (Entry) T.get();
            Entry currentAnswerEntry = new Entry(currentTEntry.index, currentTEntry.value);
            answer.append(currentAnswerEntry); // add entry at T's cursor to answer matrix
            T.moveNext();
         } else if(Q.index()!=-1){ // if Q's cursor hasn't fallen off yet (aka T's cursor has fallen off)
            currentQEntry = (Entry) Q.get();
            Entry currentAnswerEntry = new Entry(currentQEntry.index, currentQEntry.value);
            answer.append(currentAnswerEntry); // add entry at Q's cursor to answer matrix
            Q.moveNext();
         }
      }

      return answer;
   }

   // Manipulation Procedures -------------------------------------------------
   
   // makeZero()
   // sets this Matrix to the zero state
   void makeZero(){
      for(int k=1; k<=size; k++){
         row[k] = new List();
      }
      nnz = 0;
   }

   // copy()
   // returns a new Matrix having the same entries as this Matrix
   Matrix copy(){
      Matrix answer = new Matrix(size);
      Matrix zero = new Matrix(size);

      answer = this.add(zero); // add this Matrix to a zero Matrix
      return answer;
   }

   // changeEntry()
   // changes ith row, jth column of this Matrix to x
   // pre: 1<=i<=getSize(), 1<=j<=getSize()
   void changeEntry(int i, int j, double x){
      if( i<1 || i>getSize() || j<1 || j>getSize() ){
         throw new RuntimeException(
            "Matrix Error: changeEntry() called on invalid row/column");
      }

      Entry neww = new Entry(j, x); // Entry that will replace another entry
      List temp = row[i];
      Entry currentEntry;
      
      temp.moveFront(); // cursor is at beginning of List temp

      while(temp.index()!=-1){ // go from beginning to end of row
         currentEntry = (Entry) temp.get();

         if(j == currentEntry.index){ // if there is already an entry in that column
            if(x == 0.0){ // if new entry is a zero entry [[ NON-ZERO THEN ZERO ]]
               temp.delete(); // delete the old (i,j) entry that was a non-zero entry and make cursor undefined
               nnz--; // decrement # of non-zero entries bc we just replaced a non-zero entry with a zero entry
               break;
            } else { // if x!=0.0 [[ NON-ZERO THEN NON-ZERO ]]
               currentEntry.value = x; // change the value
               break;
            }
         } else if(j < currentEntry.index){ // if new Entry is before the currentEntry
            break;
         }

         temp.moveNext();
      } // break lands here
      // the above while loop ends when a entry at the spot of the new (zero) entry is deleted
      // or when an entry was just changed
      // or when the column of the new entry is to the left of the entry at the cursor

      if(temp.index()==-1 && x!=0.0){ // if cursor fell off the end of the row, [[ ZERO THEN NON-ZERO ]]
         temp.append(neww);   // then add new Entry to the end of the row
         nnz++;
      } else if(x!=0.0){ // if cursor didn't fall off the end of the row
         currentEntry = (Entry) temp.get(); // currentEntry is the entry at the cursor
         if(j != currentEntry.index){ // if new entry isn't where the currentEntry is
            temp.insertBefore(neww); // add a non-zero entry before the cursor
            nnz++;
         }
      }
      // [[ ZERO THEN ZERO ]] nothing happens
   }

   // scalarMult()
   // returns a new Matrix that is the scalar product of this Matrix with x
   Matrix scalarMult(double x){
      Matrix answer = new Matrix(this.size);
      answer = this.copy(); // answer matrix is currently a copy of the original matrix
      List currentRow;
      Entry currentEntry;

      for(int k=1; k<=this.size; k++){ // goes from row to row
         currentRow = answer.row[k];
         currentRow.moveFront(); // move cursor to the beginning of the answer row

         while(currentRow.index()!=-1){ // while cursor hasn't fallen off the row
            currentEntry = (Entry) currentRow.get();
            currentEntry.value = x*currentEntry.value;
            currentRow.moveNext();
         }
         // at this point, the cursor has fallen off the row
         answer.row[k] = currentRow;
      }

      answer.nnz = this.nnz;
      return answer;
   }

   // add()
   // returns a new Matrix that is the sum of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix add(Matrix M){
      if( this.getSize()!=M.getSize() ){
         throw new RuntimeException(
            "Matrix Error: add() called on Matrix of invalid size");
      }

      Matrix answer = new Matrix(size);

      if(this==M){ // if adding 2 of the same matrix, multiply it by 2
         return this.scalarMult(2);
      }
      for(int k=1; k<=size; k++){
         answer.row[k] = addRow(this.row[k], M.row[k]);
      }

      if(this.nnz >= M.nnz){
         answer.nnz = this.nnz;
      } else { // if (this.nnz < M.nnz)
         answer.nnz = M.nnz;
      }

      return answer;
   }

   // sub()
   // returns a new Matrix that is the difference of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix sub(Matrix M){
      if( this.getSize()!=M.getSize() ){
         throw new RuntimeException(
            "Matrix Error: sub() called on Matrix of invalid size");
      }

      Matrix negative = M.scalarMult(-1);
      Matrix answer = new Matrix(size);

      answer = this.add(negative);
      if(this==M){
         answer.nnz = 0;
      }
      return answer;
   }
   
   // transpose()
   // returns a new Matrix that is the transpose of this Matrix
   Matrix transpose(){
      int x, y;
      double z;
      List L;
      Entry entry;

      Matrix answer = new Matrix(size); // this.size?
      for(int k=1; k<=size; k++){
         L = this.row[k];
         L.moveFront(); // L is at the beginning of this matrix's current row k
         while(L.index()!= -1){ // while cursor hasn't fallen off of this matrix's current row k
            entry = (Entry) L.get();
            x = entry.index; // column of this matrix's entry
            y = k; // row of this matrix's entry
            z = entry.value; // value of this matrix's entry
            answer.changeEntry(x, y, z); // row, column, value
            L.moveNext();
         }
         
      }
      return answer;
   }

   // mult()
   // returns a new Matrix that is the product of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix mult(Matrix M){
      if( this.getSize()!=M.getSize() ){
         throw new RuntimeException(
            "Matrix Error: mult() called on Matrix of invalid size");
      }

      Matrix mversion2 = M.transpose();
      Matrix answer = new Matrix(size);

      for(int ro=1; ro<=size; ro++){
         for(int col=1; col<=size; col++){
            answer.changeEntry(ro, col, dot(this.row[ro], mversion2.row[col]));
         }
      }

      return answer;
   }
   
   // Other functions
   // overrides Object's toString() method
   public String toString(){
      String answer = "";
      for(int k=1; k<=size; k++){ // prints Matrix row-by-row
         if(row[k].length()!=0){
            answer = answer + k + ": " + row[k] + "\n";
         }
      }

      return answer;
   }
}