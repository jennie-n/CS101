//---------------------------------------------------------------------------
// Jennie Nguyen
// jnguy189
// cmps101
// 22 April 2019
// List.c
//  A List ADT that is a doubly linked list. Each node of the list contains an
//  int (the data) and 2 Node references. The List class contains three specific
//  Nodes (front, back, cursor), the length of the list, and the index of the cursor.
//  When the cursor is undefined, its index is -1.
//---------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   struct NodeObj* previous;
   int data;
   struct NodeObj* next;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes previous, data, and next fields.
// Private.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   assert(N!=NULL);
   N->previous = NULL;
   N->data = data;
   N->next = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(void){
   List L = malloc(sizeof(ListObj));
   assert(L!=NULL);
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}


// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      while( (*pL)->length!=0 ) { 
         deleteBack(*pL); // delete from the back (or the front?), shouldn't matter
      }
      free(*pL);
      *pL = NULL;
   }
}


// Access functions -----------------------------------------------------------
// length()
// Returns the length of L.
int length(List L){
   if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length);
}

// index()
// If cursor is defined, returns the index of the cursor element,
// otherwise returns -1.
int index(List L){
   if( L==NULL ){
      printf("List Error: calling index() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->index); // should work, but if not, then do if (cursor != null), return index, else return -1
}

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L){
   if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->length == 0 ){
      printf("List Error: calling front() on an empty List\n");
      exit(1);
   }
   return(L->front->data);
}

// back()
// Returns the value at the back of L.
// Pre: !isEmpty(L)
int back(List L){
   if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->length == 0 ){
      printf("List Error: calling back() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->back->data);
}

// get()
// Returns cursor element.
// Pre: !isEmpty(L), index()>=0
int get(List L){
   if( L==NULL ){
      printf("List Error: calling get() on NULL List reference\n");
      exit(1);
   }
   if( L->length == 0 || L->index < 0 ){
      printf("List Error: calling get() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->cursor->data);
}

// equals()
// Returns 1 if and only if this List and L are the same
// integer sequence. The states of the cursors in the two Lists
// are not used in determining equality.
int equals(List A, List B){
   int eq = 0;
   Node N = NULL;
   Node M = NULL;

   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}

// Manipulation procedures ----------------------------------------------------
// clear()
// Resets this List to its original empty state.
void clear(List L){
   if( L==NULL ){
      printf("List Error: calling clear() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   while(L->length!=0){
      deleteFront(L);
   }
   L->front = NULL;
   L->back = NULL;
   L->cursor = NULL;
   L->length = 0;
   L->index = -1;
}

// moveFront()
// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
   if( L==NULL ){
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(L->length > 0){
      L->cursor = L->front;
      L->index = 0;
   }
}

// moveBack()
// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
   if( L==NULL ){
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if(L->length > 0){
      L->cursor = L->back;
      L->index = (L->length)-1;
   }
}

// movePrev()
// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L){
   if( L==NULL ){
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if(L->cursor!=NULL && L->index>0){
      L->cursor = L->cursor->previous;
      L->index--;
   } else if(L->cursor!=NULL && L->index==0){
      L->cursor = NULL;
      L->index = -1;
   }
}

// moveNext()
// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L){
   if( L==NULL ){
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if( L->cursor!=NULL && L->index<((L->length)-1) ){
      L->cursor = L->cursor->next;
      L->index++;
   } else if( L->cursor!=NULL && L->index==((L->length)-1) ){
      L->cursor = NULL;
      L->index = -1;
   }
}

// prepend()
// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, int data){
   if( L==NULL ){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   Node n = newNode(data);
   if(L->front == NULL){
      L->front = L->back = n;
   } else {
      L->front->previous = n;
      n->next = L->front;
      L->front = n;
   }
   if(L->index > -1){
      L->index++;
   }
   L->length++;
}

// append()
// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data){
   if( L==NULL ){
      printf("List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   Node n = newNode(data);
   if(L->front == NULL){
      L->front = L->back = n;
   } else {
      L->back->next = n;
      n->previous = L->back;
      L->back = n;
   }
   L->length++;
}

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data){
   if( L==NULL ){
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if( L->length<=0 || L->index<0 ){
      printf("List Error: calling insertBefore() on empty List\n");
      exit(EXIT_FAILURE);
   }

   Node n = newNode(data);
   n->next = L->cursor;
   n->previous = L->cursor->previous;

   if(L->cursor->previous == NULL){
      L->front = n;
   } else {
      L->cursor->previous->next = n;
   }
   L->cursor->previous = n;

   L->index++;
   L->length++;
}

// insertAfter()
// Inserts new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data){
   if( L==NULL ){
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if( L->length<=0 || L->index<0 ){
      printf("List Error: calling insertAfter() on empty List\n");
      exit(EXIT_FAILURE);
   }
   Node n = newNode(data);
   n->previous = L->cursor;
   n->next = L->cursor->next;

   if(L->cursor->next == NULL){
      L->back = n;
   } else {
      L->cursor->next->previous = n;
   }
   L->cursor->next = n;

   L->length++;
}

// deleteFront()
// Deletes the front element. Pre: length()>0
void deleteFront(List L){
   if( L->length<=0 ){
      printf("List Error: calling deleteFront() on empty List\n");
      exit(EXIT_FAILURE);
   }

   Node n = L->front;
   if(L->length>1){
      L->front->next->previous = NULL;
      L->front = L->front->next;
   } else { // if L->length == 1
      L->front = L->back = NULL;
   }

   if(L->index == 0){
      L->index = -1;
      L->cursor = NULL;
   }
   if(L->index > -1){
      L->index--;
   }
   L->length--;
   freeNode(&n);
}

// deleteBack()
// Deletes the back element. Pre: length()>0
void deleteBack(List L){
   if( L==NULL ){
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if( L->length <= 0 ){
      printf("List Error: calling deleteBack() on empty List\n");
      exit(EXIT_FAILURE);
   }

   Node n = L->back;
   if(L->length > 1){
      L->back->previous->next = NULL;
      L->back = L->back->previous;
   } else { // if L->length == 1
      L->front = L->back = NULL;
   }

   if(L->index == L->length - 1){
      L->index = -1;
      L->cursor = NULL; // does this need to be freed??
   }
   L->length--;
   freeNode(&n);
}

// delete()
// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
   if( L==NULL ){
      printf("List Error: calling delete() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if( L->length<=0 || L->index<0 ){
      printf("List Error: calling insertBefore() on empty List\n");
      exit(EXIT_FAILURE);
   }

   Node n = L->cursor;
   if(L->cursor->next == NULL){ // if cursor is at back of list
      L->back = L->cursor->previous;
   } else {
      L->cursor->next->previous = L->cursor->previous;
   }

   if(L->cursor->previous == NULL){ // if cursor is at front of list
      L->front = L->cursor->next;
   } else {
      L->cursor->previous->next = L->cursor->next;
   }

   L->length--;
   L->cursor = NULL;
   L->index = -1;
   freeNode(&n);
}


// Other Functions ------------------------------------------------------------

// printList()
// prints a text representation of L to the file pointed to by out
void printList(FILE* out, List L){
   if( L==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   for(Node N = L->front; N != NULL; N = N->next){
      fprintf(out, "%d ", N->data);
   }
}

// copyList()
// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L){
   if( L==NULL ){
      printf("List Error: calling copyList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   List neww = newList();
   Node n = L->front;

   while(n != NULL){
      append(neww, n->data);
      n = n->next;
   }

   neww->index = -1;
   neww->cursor = NULL;
   return neww;
}

// concatList()
// Returns a new List which is the concatenation of
// this list followed by L. The cursor in the new List
// is undefined, regardless of the states of the cursors
// in this List and L. The states of this List and L are
// unchanged.
List concatList(List A, List B){
   if( A==NULL || B==NULL ){
      printf("List Error: calling concatList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   List concatenation = newList();
   concatenation = copyList(A); // at this point, concatenation is a copy of List A

   Node n = B->front;
   while(n != NULL){
      append(concatenation, n->data);
      n = n->next;
   }

   concatenation->index = -1;
   concatenation->cursor = NULL;
   return concatenation;
}