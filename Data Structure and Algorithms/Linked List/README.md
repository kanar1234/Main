------------------------------ Description ------------------------------

Implements a graph data structure with functions for adding edges, performing breadth-first search (BFS), and finding shortest paths. Includes features to retrieve graph properties like order, size, source, parent, and distance.

------------------------------ How to run -------------------------------

GraphClient.c/GraphTest.c -

- Change value of EXEBIN to GraphClient or GraphTest whichever you want to use in Makefile

- Modify the graphs or functions in GraphClient.c or GraphTest.c to whatever functions you want to test below

- Call make to create the application

- Run the created application 

Constructor For Linked List used that will be used as a base for future programs

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

----------------------------------------------List Functions----------------------------------------------

-----Exported type-----

typedef struct ListObj* List;


-----Constructors-Destructors-----

List newList(void); // Creates and returns a new empty List.

void freeList(List* pL); // Frees all heap memory associated with *pL, and sets *pL to NULL.

-----Access functions-----

int length(List L); // Returns the number of elements in L.

int index(List L); // Returns index of cursor element if defined, -1 otherwise.

int front(List L); // Returns front element of L. Pre: length()>0

int back(List L); // Returns back element of L. Pre: length()>0

int get(List L); // Returns cursor element of L. Pre: length()>0, index()>=0

int equals(List A, List B); // Returns true (1) if Lists A and B are in same state, and returns false (0) otherwise.

-----Manipulation procedures-----

void clear(List L); // Resets L to its original empty state.

void moveFront(List L); // If L is non-empty, sets cursor under the front element, otherwise does nothing

void moveBack(List L); // If L is non-empty, sets cursor under the back element, otherwise does nothing
void movePrev(List L); // If cursor is defined and not at front, move cursor one step toward the front of L; if cursor is defined and at
front, cursor becomes undefined; if cursor is undefined
do nothing

void moveNext(List L); // If cursor is defined and not at back, move cursor one
step toward the back of L; if cursor is defined and at
back, cursor becomes undefined; if cursor is undefined
do nothing

void prepend(List L, int data); // Insert new element into L. If L is non-empty,
insertion takes place before front element.
 
void append(List L, int data); // Insert new element into L. If L is non-empty,
insertion takes place after back element.

void insertBefore(List L, int data); // Insert new element before cursor.
Pre: length()>0, index()>=0

void insertAfter(List L, int data); // Insert new element before cursor.
Pre: length()>0, index()>=0

void deleteFront(List L); // Delete the front element. Pre: length()>0

void deleteBack(List L); // Delete the back element. Pre: length()>0

void delete(List L); // Delete cursor element, making cursor undefined.
Pre: length()>0, index()>=0

-----Other operations-----

void printList(FILE* out, List L); // Prints to the file pointed to by out, a
string representation of L consisting
of a space separated sequence of integers,
string representation of L consisting
of a space separated sequence of integers,
with front on left.

List copyList(List L); // Returns a new List representing the same integer
sequence as L. The cursor in the new list is undefined,
regardless of the state of the cursor in L. The state
of L is unchanged.

int isPalindrome(List L); //Returns 1 if L is a palindrome otherwise returns 0
