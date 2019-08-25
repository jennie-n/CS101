//-----------------------------------------------------------------------------
//  Jennie Nguyen
//  jnguy189
//  cmps101
//  6 May 2019
//  List.java
// 
//  A List ADT that is a doubly linked list. Each node of the list contains an
//  Object (the data) and 2 Node references. The List class contains three specific
//  Nodes (front, back, cursor), the length of the list, and the index of the cursor.
//  When the cursor is undefined, its index is -1.
//-----------------------------------------------------------------------------

class List{

   private class Node{
      // Fields
      Node previous;
      Object data;
      Node next;
      
      // Constructor
      Node(Object data) {
         previous = null;
         this.data = data;
         next = null;
      }
      
      // toString():  overrides Object's toString() method
      public String toString() { 
         return String.valueOf(data); 
      }
      
      // equals(): overrides Object's equals() method
      public boolean equals(Object x){
         boolean eq = false;
         Node that;
         if(x instanceof Node){
            that = (Node) x;
            eq = (this.data==that.data);
         }
         return eq;
      }
   }

   // Fields
   private Node front;
   private Node back;
   private Node cursor;
   private int length;
   private int index;

   // Constructor
   List() { 
      front = back = cursor = null; 
      length = 0;
      index = -1;
   }


   // Access Functions --------------------------------------------------------

   // length()
   // Returns the number of elements in this List.
   int length(){
      return length;
   }

   // index()
   // If cursor is defined, returns the index of the cursor element,
   // otherwise returns -1.
   int index(){
      if(cursor != null){
         return index;
      } else {
         return -1;
      }
   }

   // isEmpty()
   // Returns true if this List is empty, false otherwise.
   boolean isEmpty() { 
      return length==0; 
   }

   // front() 
   // Returns front element.
   // Pre: length()>0
   Object front(){
      if( this.length()<=0 ){
         throw new RuntimeException(
            "List Error: front() called on empty List");
      }
      return front.data;
   }

   // back() 
   // Returns back element.
   // Pre: length()>0
   Object back(){
      if( this.length()<=0 ){
         throw new RuntimeException(
            "List Error: back() called on empty List");
      }
      return back.data;
   }

   // get() 
   // Returns cursor element.
   // Pre: length()>0, index()>=0
   Object get(){
      if( this.index()<0 ){
         throw new RuntimeException(
            "List Error: get() called on invalid cursor");
      }
      if( this.length()<=0 ){
         throw new RuntimeException(
            "List Error: get() called on empty List");
      }
      return cursor.data;
   }

   // equals()
   // Returns true if and only if this List and L are the same
   // integer sequence. The states of the cursors in the two Lists
   // are not used in determining equality.
   public boolean equals(Object x){
      boolean eq  = false;
      Node N, M;
      List L;

      if(x instanceof List){
         L = (List) x;
         N = this.front;
         M = L.front;
         eq = (this.length==L.length); // compare lengths of this List and L
         while( eq && N!=null ){
            eq = N.equals(M);
            N = N.next;
            M = M.next;
         }
      }
      return eq;
   }

   // Manipulation Procedures -------------------------------------------------

   // clear()
   // Resets this List to its original empty state.
   void clear(){
      front = null;
      back = null;
      cursor = null;
      length = 0;
      index = -1;
   }

   // moveFront()
   // If List is non-empty, places the cursor under the front element,
   // otherwise does nothing.
   void moveFront(){
      if(length>0){ // if the List is non-empty
         cursor = front;
         index = 0;
      }
   }

   // moveBack()
   // If List is non-empty, places the cursor under the back element,
   // otherwise does nothing.
   void moveBack(){ // if the List is non-empty
      if(length>0){
         cursor = back;
         index = length-1;
      }
   }

   // movePrev()
   // If cursor is defined and not at front, moves cursor one step toward
   // front of this List, if cursor is defined and at front, cursor becomes
   // undefined, if cursor is undefined does nothing.
   void movePrev(){
      if( cursor!=null && index>0 ){
         cursor = cursor.previous;
         index = index-1;
      } else if( cursor!=null && index==0 ){
         cursor = null;
         index = -1;
      }
   }

   // moveNext()
   // If cursor is defined and not at back, moves cursor one step toward
   // back of this List, if cursor is defined and at back, cursor becomes
   // undefined, if cursor is undefined does nothing.
   void moveNext(){
      if( cursor!=null && index<length-1 ){
         cursor = cursor.next;
         index = index+1;
      } else if( cursor!=null && index==length-1 ){
         cursor = null;
         index = -1;
      }
   }

   // prepend()
   // Insert new element into this List. If List is non-empty,
   // insertion takes place before front element.
   void prepend(Object data){
      Node newNode = new Node(data);
      if(front==null){
         front = newNode;
         back = newNode;
      } else{
         front.previous = newNode;
         newNode.next = front;
         front = newNode;
      }
      if(index>-1){
         index++;
      }
      length++;
   }

   // append()
   // Insert new element into this List. If List is non-empty,
   // insertion takes place after back element.
   void append(Object data){
      Node newNode = new Node(data);
      if(front==null){
         front = newNode;
         back = newNode;
      } else {
         back.next = newNode;
         newNode.previous = back;
         back = newNode;
      }
      length++;
   }

   // insertBefore()
   // Insert new element before cursor.
   // Pre: length()>0, index()>=0
   void insertBefore(Object data){
      Node newNode = new Node(data);
      if( length()<=0 || index()<0 ){
         throw new RuntimeException(
            "List Error: insertBefore() called on empty List");
      }

      newNode.next = cursor;
      newNode.previous = cursor.previous;

      if(cursor.previous == null){
         front = newNode;
      } else {
         cursor.previous.next = newNode;
      }
      cursor.previous = newNode;

      index++;
      length++;
   }

   // insertAfter()
   // Inserts new element after cursor.
   // Pre: length()>0, index()>=0
   void insertAfter(Object data){
      Node newNode = new Node(data);
      if( length()<=0 || index()<0 ){
         throw new RuntimeException(
            "List Error: insertAfter() called on empty List");
      }

      newNode.previous = cursor;
      newNode.next = cursor.next;

      if(cursor.next == null){
         back = newNode;
      } else {
         cursor.next.previous = newNode;
      }

      cursor.next = newNode;
 
      length++;
   }

   // deleteFront()
   // Deletes the front element. Pre: length()>0
   void deleteFront(){
      if( length()<=0 ){
         throw new RuntimeException(
            "List Error: deleteFront() called on empty List");
      }

      if(length()>1){
         front.next.previous = null;
         front = front.next;
      } else { // if length == 1
         front = back = null;
      }

      if(index==0){
         index = -1;
         cursor = null;
      }
      if(index>-1){
         index--;
      }
      length--;
   }

   // deleteBack()
   // Deletes the back element. Pre: length()>0
   void deleteBack(){
      if( length()<=0 ){
         throw new RuntimeException(
            "List Error: deleteBack() called on empty List");
      }

      if(length()>1){
         back.previous.next = null;
         back = back.previous;
      } else { // if length == 1
         front = back = null;
      }

      if(index == length-1){
         index = -1;
         cursor = null;
      }
      length--;
   }

   // delete()
   // Deletes cursor element, making cursor undefined.
   // Pre: length()>0, index()>=0
   void delete(){
      if( length()<=0 || index()<0 ){
         throw new RuntimeException(
            "List Error: delete() called on empty List");
      }

      if(cursor.next == null){ // if cursor is at back of list
         back = cursor.previous;
      } else {
         cursor.next.previous = cursor.previous;
      }

      if(cursor.previous == null){ // if cursor is at front of list
         front = cursor.next;
      } else {
         cursor.previous.next = cursor.next;
      }

      length--;
      cursor = null;
      index = -1;
   }


   // Other Methods ---------------------------------------------------------

   // toString()
   // Overrides Object's toString method. Returns a String
   // representation of this List consisting of a space
   // separated sequence of integers, with front on left.
   public String toString(){
      StringBuffer sb = new StringBuffer();
      Node N = front;
      while(N!=null){
         sb.append(N.toString());
         sb.append(" ");
         N = N.next;
      }
      return new String(sb);
   }

}
