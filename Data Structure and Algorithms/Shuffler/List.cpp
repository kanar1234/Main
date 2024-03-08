//-----------------------------------------------------------------------------
// Alan Szeto
// 1672580
// pa7
// Queue.cpp
// Implementation file for Queue ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include"List.h"

using namespace std;

// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(int x){
   data = x;
   next = nullptr;
   prev = nullptr;
}


// Class Constructors & Destructors -------------------------------------------

// Creates a new Queue in the empty state.
List::List(){
	frontDummy = new Node(-69);
	backDummy = new Node(-69);
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	
	// frontDummy->next = backDummy;
	// backDummy->prev = frontDummy;
	beforeCursor->next = backDummy;
	afterCursor->prev = frontDummy;
	
	pos_cursor = 0;
	num_elements = 0;
}

// Copy Constructor.
List::List(const List& L){
	// make this an empty List
	frontDummy = new Node(-69);
	backDummy = new Node(-69);
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor->next = backDummy;
	afterCursor->prev = frontDummy;
	
	pos_cursor = 0;
	num_elements = 0;
	
	// if(L.frontDummy->next != L.backDummy)
	// {
	Node* N = L.frontDummy->next;
	while(N != L.backDummy)
	{
		insertBefore(N->data);
		N = N->next;
	}	
	//moveFront();
}

// Destructor
List::~List(){
   clear();
   delete(frontDummy);
   delete(backDummy);
}


// Access functions -----------------------------------------------------------

// isEmpty()
// Returns true if this List is empty, false otherwise.
bool List::isEmpty(){
	bool empty = false;
	if( num_elements == 0 )
		empty = true;
   return(empty);
}

// size()
// Returns the size of this List.
int List::size(){
   return(num_elements);
}
// position()
// Returns the position of the cursor in this List. The value returned
// will be in the range 0 to size().
int List::position(){
   return(pos_cursor);
}

// // Manipulation procedures ----------------------------------------------------

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
	pos_cursor = 0;
	afterCursor = frontDummy->next;
	beforeCursor = frontDummy;
}

// moveBack()
// Moves cursor to position size() in this List.
void List::moveBack(){
	pos_cursor = num_elements;
	afterCursor = backDummy;
	beforeCursor = backDummy->prev;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<size()
int List::peekNext(){
	return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
int List::peekPrev(){
	return beforeCursor->data;
}  

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<size() 
int List::moveNext(){
	if(pos_cursor > num_elements-1)
	{
		cerr << "List Error: calling moveNext() on an empty List" << endl;
		exit(EXIT_FAILURE);
	}
	beforeCursor = beforeCursor->next;
	afterCursor = afterCursor->next;
	pos_cursor ++;
	
	//cout << "node is " << beforeCursor->data << endl;
	//cout << "node prev is " << beforeCursor->prev->data << endl;
	//cout << "node next is " << beforeCursor->next->data << endl;
	
	return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
int List::movePrev(){
	if(pos_cursor <= 0)
	{
		cerr << "List Error: calling movePrev() on an empty List" << endl;
		exit(EXIT_FAILURE);
	}
	beforeCursor = beforeCursor->prev;
	afterCursor = afterCursor->prev;
	pos_cursor --;
	//cout << "node is " << beforeCursor->data << endl;
	//cout << "node prev is " << beforeCursor->prev->data << endl;
	//cout << "node next is " << beforeCursor->next->data << endl;
	return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(int x){
	Node* p = new Node(x);
	
	afterCursor->prev = p;
	beforeCursor->next = p;
	p->next = afterCursor;
	p->prev = beforeCursor;
	afterCursor = p;
	
	num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(int x){
	Node* p = new Node(x);
	
	beforeCursor->next = p;
	afterCursor->prev = p;
	p->next = afterCursor;
	p->prev = beforeCursor;
	beforeCursor = p;
	
	num_elements++;
	pos_cursor++;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<size()
void List::eraseAfter(){
	if(pos_cursor > num_elements-1)
	{
		cerr << "Out of bound Error: calling eraseAfter() out of range" << endl;
		exit(EXIT_FAILURE);
	}
	
	if(num_elements == 0)
	{
		cerr << "Out of bound Error: calling eraseAfter() on an empty node" << endl;
		exit(EXIT_FAILURE);
	}
	
	Node* n = afterCursor;
	beforeCursor->next = afterCursor->next;
	afterCursor->next->prev = beforeCursor;
	afterCursor = afterCursor->next;
	n->next = nullptr;
	n->prev = nullptr;
	delete(n);
	num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
	if(pos_cursor < 1)
	{
		cerr << "Out of bound Error: calling eraseAfter() out of range" << endl;
		exit(EXIT_FAILURE);
	}
	if(num_elements == 0)
	{
		cerr << "Out of bound Error: calling eraseAfter() on an empty node" << endl;
		exit(EXIT_FAILURE);
	}
	
	Node* n = beforeCursor;
	beforeCursor->prev->next = afterCursor;
	afterCursor->prev = beforeCursor->prev;
	beforeCursor = beforeCursor->prev;
	n->next = nullptr;
	n->prev = nullptr;
	delete(n);
	pos_cursor--;
	num_elements--;
}

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of the element x.
// If x is found, places the cursor immediately after the found element (so 
// eraseBefore() would remove the found element), and returns the final 
// cursor position. If x is not found, places the cursor at position size(),
// and returns -1. 
int List::findNext(int x){
	int num = -1;
	while(afterCursor != backDummy && num == -1)
	{
		if(afterCursor->data == x)
		{
			moveNext();
			num = pos_cursor;
		}
		else
			moveNext();
	}
	if(num == -1)
	{
		pos_cursor = num_elements;
		moveBack();
	}
	return num;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of the element x.
// If x is found, places the cursor immediately before the found element (so 
// eraseAfter() would remove the found element), and returns the final 
// cursor position. If x is not found, places the cursor at position 0, and 
// returns -1. 
int List::findPrev(int x){
	int num = -1;
	while(beforeCursor != frontDummy && num == -1)
	{
		if(beforeCursor->data == x)
		{
			movePrev();
			num = pos_cursor;
		}
		else
			movePrev();
	}
	return num;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique data
// values. The order of the remaining elements is obtained by retaining
// the frontmost occurrance of each element, and removing all other 
// occurances. The cursor is not moved with respect to the retained 
// elements, i.e. it lies between the same two retained elements that it 
// did before cleanup() was called.
void List::cleanup(){
	int pos = pos_cursor;
	moveFront();
	while(afterCursor != backDummy)
	{
		moveNext();
		int dupe = beforeCursor->data;
		while(findNext(dupe) != -1)
		{
			eraseBefore();
			if( pos_cursor < pos )
			{
				pos--;
			}
		}
		findPrev(dupe);
		moveNext();
	}
	moveFront();
	for(int i = 0; i < pos; i++)
		moveNext();
}

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
	if(num_elements > 0)
	{
		Node* N = frontDummy->next;
		while(N != backDummy)
		{
			Node* del = N;
			N = N->next;
			num_elements--;
			delete(del);
		}
	}
	pos_cursor = 0;
}
   
// concat()
// Returns a new List consisting of the elements of this List, followed
// the elements of L. The returned List's cursor will be at its front
// (position 0).
List List::concat(const List& L){
	List J;
	Node* N = frontDummy->next;
	while( N!= backDummy ){
		J.insertBefore(N->data);
		N = N->next;
		//J.num_elements++;
	}
	
	Node* M = L.frontDummy->next;
	while( M != L.backDummy ){
		J.insertBefore(M->data);
		M = M->next;
		//J.num_elements++;
	}
	J.moveFront();
	// cout << "position is " << J.position() << endl;
	// cout << "node is " << J.beforeCursor->data << endl;
	// cout << "node next is " << J.afterCursor->data << endl;
	// cout << "node prev is " << J.beforeCursor->data << endl;
	
	return J;
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
string List::to_string(){
	Node* N;
	string s = "";

	for(N=frontDummy->next; N!=backDummy; N=N->next){
		s += std::to_string(N->data)+" ";
	}
	return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R){
	bool eq = false;
   Node* N;
   Node* M;

   eq = ( this->num_elements == R.num_elements );
   N = this->frontDummy;
   M = R.frontDummy;
   while( eq && N!=backDummy){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
ostream& operator<<( ostream& stream, List& L ){
   return stream << L.List::to_string();
}
   
// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged are unchanged.
bool operator==( List& A, const List& B ){
	return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
	if( this != &L ){ // not self assignment
      // make a copy of L
      List temp = L;

      // then swap the copy's fields with fields of this
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
	  std::swap(beforeCursor, temp.beforeCursor);
	  std::swap(afterCursor, temp.afterCursor);
      //std::swap(pos_cursor, temp.pos_cursor); //makes concat position fail
	  std::swap(num_elements, temp.num_elements);
   }

   // return this with the new data installed
   return *this;

   // the copy, if there is one, is deleted upon return
}
