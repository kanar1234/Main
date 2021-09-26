//-----------------------------------------------------------------------------
// Alan Szeto
// 1672580
// pa2
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   void* data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int index;
   int length;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(void* data, Node nPrev, Node nNext){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = nNext;
   N->prev = nPrev;
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
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}


// freeList()
// Frees all heap memory associated with List *pQ, and sets *pQ to NULL.S
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      Node temp = (*pL)->front;
	  while (temp != NULL){
		  Node current = temp;
		  temp = temp->next;
		  free(current);
   }
   
   //removes the last bit of memory that's still in the pointer of pQ
   free(*pL);
   *pL = NULL;
	}
}


// Access functions -----------------------------------------------------------

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
void* front(List L){
   if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
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
void* back(List L){
   if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   if( L->length == 0 ){
      printf("List Error: calling back() on an empty List\n");
      exit(1);
   }
   return(L->back->data);
}

// length()
// Returns the length of L.
int length(List L){
   if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(1);
   }
   return(L->length);
}

// index()
// Returns the index of L.
int index(List L){
   if( L==NULL ){
      printf("List Error: calling index() on NULL List reference\n");
      exit(1);
   }
   return(L->index);
}

// get()
// Returns the element of L.
void* get(List L){
   if( L==NULL || L->length == 0 || L->index <0){
      printf("List Error: calling get() on NULL List reference\n");
      exit(1);
   }
   return(L->cursor->data);
}

/*/ isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L){
   if( L==NULL ){
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(1);
   }
   return(L->length==0);
}*/

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to empty space
void clear(List L)
{
   if( L==NULL ){
      printf("List Error: calling clear() on NULL List reference\n");
      exit(1);
   }
   Node temp = L->front;
   while( temp != NULL ){
	    Node current = temp;
		temp = temp->next;
		free(current);
   }
   //After all nodes are deallocated, we set front, back and cursor to null
   //and set length to 0 and index to -1
   L->front = NULL;
   L->back = NULL;
   L->cursor = NULL;
   L->length = 0;
   L->index = -1;
	
}

// moveFront()
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
// Pre: !isEmpty(Q)
void moveFront(List L){
	if( L==NULL ){
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(1);
   }
	else{
		L->cursor = L->front;
		L->index = 0;
	}
}

// moveBack()
// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
// Pre: !isEmpty(Q)
void moveBack(List L){
	if( L==NULL ){
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(1);
   }
   //set cursor to back element and length++
	else{
		L->cursor = L->back;
		L->index = L->length-1;
	}
}

// movePrevious()
// If L is non-empty, sets cursor under the previous element,
// otherwise does nothing.
// Pre: !isEmpty(Q)
void movePrev(List L){
	if( L==NULL ){
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(1);
   }
    //move cursor to previous node
	if( L->cursor != NULL && L->index >0){
		L->cursor = L->cursor->prev;
		L->index = L->index - 1;
	}
	//moves cursor to null if cursor is at the first element
	else if( L->index <= 0){
		L->cursor = NULL;
		L->index = -1;
	}
}

// moveNext()
// If L is non-empty, sets cursor under the next element,
// otherwise does nothing.
// Pre: !isEmpty(Q)
void moveNext(List L){
	if( L==NULL ){
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(1);
   }
   //moves cursor to next value
	if( L->cursor != NULL && L->index < L->length - 1){
		L->cursor = L->cursor->next;
		L->index = L->index + 1;
	}
	//moves cursor to null if cursor is at back
	else if(L->cursor != NULL && L->index == L->length-1){
		L->cursor = NULL;
		L->index = -1;
	}
}

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, void* data){
	if( L==NULL ){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(1);
	}
	//temporary node that points to the nodes in L 
	//if list is empty, sets back and front to NULL
	Node p = newNode(data, L->front, NULL);
	if( L->length >= 0){
		L->index ++;
		}		
	if(L->length == 0)
	{
		p->next = NULL;
		L->back = p;
	}
	//adds node to start of L	
	else{
		L->back->prev = p;
		}
	//increase the length by 1
	L->front = p;
	L->length ++;
}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, void* data){
	if( L==NULL ){
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
	}
	//temporary node that points to the nodes in L starting from front
	//if list is empty, sets back and front to NULL
	Node p = newNode(data, L->back, NULL);
	if( L->length == 0){
		p->prev = NULL;
		L->front = p;
		}		
	//adds node to end of L	
	else{
		L->back->next = p;
		}
	//increase the length by 1
	L->back = p;
	L->length = L->length + 1;
}

// Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertBefore(List L, void* data){
	if( L==NULL || L->length == 0 || L->index < 0){
      printf("List Error: calling insertBefore() on NULL or empty List reference\n");
      exit(1);
	}	
	//make new node pointing at node before cursor and cursor
	Node p = newNode(data, L->cursor->prev, L->cursor);
	//if cursor is at first node, set front to p and 
	//link previous of cursor to the new node
	if(L->index != 0){
		L->cursor->prev = p;
	}
	//link node before cursor to new node and link 
	//previous of cursor to new node
	else{
		L->front = p;
	}
	//increase length
	L->cursor->prev = p;
	L->index++;
	L->length++;
}

// Insert new element before cursor.
 // Pre: length()>0, index()<=lenght-1
void insertAfter(List L, void* data){
	if( L==NULL || L->length == 0 || L->index < 0){
      printf("List Error: calling insertAfter() on NULL or empty List reference\n");
      exit(1);
	}	
	//make new node pointing at node after cursor and cursor
	Node p = newNode(data, L->cursor, L->cursor->next);
	//if cursor is at last node, set back to p and 
	//link previous of cursor to the new node
	if(L->index != L->length-1){
		L->cursor->next->prev = p;
	}
	//link node before cursor to new node and link 
	//previous of cursor to new node
	else{
		L->back = p;
	}
	//increase length
	L->cursor->next = p;
	L->length++;
}
// Delete the front element. Pre: length()>0)
void deleteFront(List L){
	if( L==NULL || L->length < 1){
      printf("List Error: calling deleteFront() on NULL or empty List reference\n");
      exit(1);
	}	
	//if there is only one node, delete it
	if(L->length == 1){
		L->cursor = NULL;
		L->index = -1;
	}
	//deletes front node and length--
	Node p = L->front;
	L->front = L->front->next;
	if(L->length == 1)
	{
		L->front->prev = NULL;
	}
	L->index --;
	L->length --;
	freeNode(&p);
	}

// Delete the back element. Pre: length()>0)
void deleteBack(List L){
	if( L==NULL || L->length < 1){
      printf("List Error: calling deleteBack() on NULL or empty List reference\n");
      exit(1);
	}	
	//if there is only one node, delete it
	if(L->length == 1){
		L->cursor = NULL;
		L->index = -1;
	}
	//deletes back node, length-- index --
	Node p = L->back;
	L->back = L->back->prev;
	if(L->length != 1)
	{
		L->back->next = NULL;
	}
	L->index--;
	L->length--;
	freeNode(&p);
	}
	
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
	if( L==NULL || L->length <= 0 || L->index <0){
      printf("List Error: calling delete() on NULL or empty List reference\n");
      exit(1);
	}	
	//temp node so we can delete it
	//after removing links
	//if cursor is at fist node, set prev to null
	Node p = L->cursor;
	if( L->index == 0){
		L->front = L->front->next;
		L->front->prev = NULL;
	}
	//if cursor is at last node, set next to null
	else if(L->index == L->length-1){
		L->back = L->back->prev; 
		L->back->next = NULL;
	}
	//link left of cursor with right of cursor and vice versa
	else{
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
	}
	L->cursor = NULL;
	L->index = -1;
	L->length = L->length -1;
	freeNode(&p);
}
// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in Q on a single line to stdout.
// Prints to the file pointed to by out, a
 // string representation of L consisting
 // of a space separated sequence of integers,
void printList(FILE* out, List L){
Node N = NULL;

   if( L==NULL ){
      printf("Queue Error: calling printQueue() on NULL Queue reference\n");
      exit(1);
   }
	else{
	   for(N = L->front; N != NULL; N = N->next){
		  printf("%p ", N->data);
	   }
	printf("\n");
	}
}