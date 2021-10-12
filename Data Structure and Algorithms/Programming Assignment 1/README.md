Lex.c:
Sorts input file and outputs sorted version of input using insertion sort in O(n^2) time

List.h:
Header file for List functions

ListClient.c:
Given - Tests the List ADT

Makefile:
Given - Compiles the program

List.c:
Creates a doubly linked list and List ADT

List Functions ----------------------------------------------------------------------------------------

newNode(int data, Node prev, Node next) - creates a new node that initializes the index to -1, node value to data, size to 0, and prev/next to NULL

freeNode(Node* pN) - frees node pN

newList(void) - creates a new list

freeList(List* pL) - frees list pL

front(List L) - returns the first node in L

back(List L) - returns the last node in L

index(List L) - returns current index

get(List L) - returns value at current index

isEmpty(List L) - returns 1 if list is empty else returns 0

equals(List A, List B) - returns 1 if A = B else returns 0

clear(List L) - deallocates all nodes and sets everything to its initial values

moveFront(List L) - moves index to the first node

moveBack(List L) - moves index to the last node

movePrevious(List L) - moves index to the previous node if it exists

moveNext(List L) - moves index to the next node if it exists

prepend(List L, int data) - adds a node to the front of L with value = data

append(List L, int data) - adds a node to the back of L with value = data

insertBefore(List L, int data) - adds a node between the current index and the previous index

insertAfter(List L, int data) - adds a node between the current index and the next index

deleteFront(List L) - pops the node in L

deleteBack(List L) - dequeues node in L

delete(List L) - deletes node in current index and sets index to -1

printList(List L) - prints list onto terminal

copyList(List L) - returns a copy of L
