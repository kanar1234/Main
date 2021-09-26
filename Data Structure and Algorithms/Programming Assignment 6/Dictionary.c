//-----------------------------------------------------------------------------
// Alan Szeto
// 1672580
// pa6
// Dictionary.c
// Binary Search Tree implementation of the Dictionary ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"
#define BLACK -1
#define RED -2
// Private Types and Functions ------------------------------------------------

// NodeObj
typedef struct NodeObj
{
   char* key;
   int* value;
   int color;
   struct NodeObj* parent;
   struct NodeObj* left;
   struct NodeObj* right;
} NodeObj;

static NodeObj nil = {.key = KEY_UNDEF, .value = VAL_UNDEF, .color = BLACK, .parent = NULL, .left = NULL, .right = NULL};

// Node
typedef NodeObj* Node;

static const Node NIL = &nil;

// newNode()
// Constructor for Node type.
Node newNode(KEY_TYPE k, VAL_TYPE v) 
{
   Node N = malloc(sizeof(NodeObj));
   N->key = k;
   N->value = v;
   N->color = BLACK;
   N->left = N->right = N->parent = NIL;
   return(N);
}


// freeNode()
// Destructor for Node type
void freeNode(Node* pN)
{
   if( pN!=NULL && *pN!=NULL )
   {
      free(*pN);
      *pN = NULL;
   }
}

// DictionaryObj
typedef struct DictionaryObj
{
   Node root;
   int numPairs;
   int unique;
   Node cursor;
} DictionaryObj;

// findKey()
// Returns the Node containing key k in the subtree rooted at R, or returns 
// KEY_UNDEF if no such Node exists.
Node findKey(Node R, KEY_TYPE k)
{
   if(R == NIL || KEY_CMP(k, R->key)== 0) 
      return R;
   if( KEY_CMP(k, R->key)<0 ) 
      return findKey(R->left, k);
   else // strcmp(k, R->key)>0
      return findKey(R->right, k);
}

// findValue()
// Returns the value containing key k in the subtree rooted at R, or returns 
// VAL_UNDEF if no such Node exists.
// int findValue(Node R, KEY_TYPE k)
// {
   // if(R == NIL || KEY_CMP(k, R->key)== 0) 
      // return R->value;
   // if( KEY_CMP(k, R->key)<0 ) 
      // return findValue(R->left, k);
   // else // strcmp(k, R->key)>0
      // return findValue(R->right, k);
// }

// findParent()
// Returns the parent of N in the subtree rooted at R, or returns NULL if N is
// equal to R. 
// Pre: R != NULL
Node findParent(Node N, Node R)
{
   Node P = NIL;
   if( N!=R )
   {
      P = R;
      while( P->left!=N && P->right!=N )
	  {
         if(KEY_CMP(N->key, P->key)<0)
            P = P->left;
         else
            P = P->right;
      }
   }
   return P;
}

// deleteAll()
// deletes all Nodes in the subtree rooted at R.
void deleteAll(Node R)
{
   if( R!=NIL )
   {
      deleteAll(R->left);
      deleteAll(R->right);
      freeNode(&R);
   }
}

// findLeftmost()
// Returns the leftmost Node in the subtree rooted at R, or KEY_UNDEF if R is NULL.
Node findLeftmost(Node R)
{
   Node L = R;
   while( L->left != NIL ) 
   {
	   //fprintf(stdout, "key is: %s\n",L->key);
	   L = L->left;
   }
   //fprintf(stdout, "last value is: %i\n",L->value);
   return L;
}

// findRightmost()
// Returns the rigghtmost Node in the subtree rooted at R, or KEY_UNDEF if R is NULL.
Node findRightmost(Node R)
{
   Node L = R;
   while( L->right != NIL ) 
   {
	   //fprintf(stdout, "key is: %s\n",L->key);
	   L = L->right;
   }
   //fprintf(stdout, "last value is: %i\n",L->value);
   return L;
}

//TreeSuccessor(x)
//Returns the next Node after x
Node TreeSuccessor(Node x)
{
   if(x->right != NIL)
      return findLeftmost(x->right);
   Node y = x->parent;
   while(y != NIL && x == y->right)
   {
      x = y;
      y = y->parent;
   }
   return y;
}

//TreePredecessor(x)
//Returns the next Node after x
Node TreePredecessor(Node x)
{
   if(x->left != NIL)
      return findRightmost(x->left);
   Node y = x->parent;
   while(y != NIL && x == y->left)
   {
      x = y;
      y = y->parent;
   }
   return y;
}

//Transplant(T,u,v)
//replaces subtree u with v
void Transplant(Dictionary T, Node u, Node v)
{
   if(u->parent == NIL)
      T->root = v;
   else if(u == u->parent->left)
      u->parent->left = v;
   else 
      u->parent->right = v;
   if (v != NIL)
      v->parent = u->parent;
}

//LeftRotate(T,x)
//helper function for rbt insert helper function
void LeftRotate(Dictionary T, Node x)
{
   // set y
   Node y = x->right ;
   
   // turn y's left subtree into x's right subtree
   x->right = y->left; 
   if(y->left != NIL)
      y->left->parent = x;
   
   // link x's parent to y
   y->parent = x->parent; 
   if(x->parent == NIL)
      T->root = y;
   else if(x == x->parent->left)
      x->parent->left = y;
   else 
      x->parent->right = y;
   
   // put x on y's left
   y->left = x; 
   x->parent = y;
}

//RightRotate(T, x)
//helper function for rbt insert helper function
void RightRotate(Dictionary T, Node x)
{
   // set y
   Node y = x->left; 
   
   // turn y's right subtree into x's left subtree
   x->left = y->right; 
   if(y->right != NIL)
      y->right->parent = x;
   
   // link x's parent to y
   y->parent = x->parent; 
   if(x->parent == NIL)
      T->root = y;
   else if(x == x->parent->right)
      x->parent->right = y;
   else 
      x->parent->left = y;
   
   // put x on y's right
   y->right = x; 
   x->parent = y;
}

//helper function for RBT insert
void RB_InsertFixUp(Dictionary T, Node z)
{
	Node y;
   while(z->parent->color == RED)
   {
      if(z->parent == z->parent->parent->left)
	  {
         y = z->parent->parent->right;
         if(y->color == RED)
		 {
            z->parent->color = BLACK;              // case 1
            y->color = BLACK;                     // case 1
            z->parent->parent->color = RED;         // case 1
            z = z->parent->parent;                 // case 1
		 }
         else 
		 {
            if(z == z->parent->right)
			{
               z = z->parent;                     // case 2
               LeftRotate(T, z);                 // case 2
			}
            z->parent->color = BLACK;              // case 3
            z->parent->parent->color = RED;         // case 3
            RightRotate(T, z->parent->parent);     // case 3
		 }
	  }
      else
	  {		  
         y = z->parent->parent->left;
         if(y->color == RED)
		 {
            z->parent->color = BLACK;              // case 4
            y->color = BLACK;                     // case 4
            z->parent->parent->color = RED;         // case 4
            z = z->parent->parent;                 // case 4
		 }
         else 
		 {
            if(z == z->parent->left)
			{
               z = z->parent;                     // case 5
               RightRotate(T, z);                // case 5
			}
            z->parent->color = BLACK;              // case 6
            z->parent->parent->color = RED;         // case 6
            LeftRotate(T, z->parent->parent);      // case 6
		 }
	  }
   }
   T->root->color = BLACK;
}

void RB_Transplant(Dictionary T, Node u, Node v)
{
   if(u->parent == NIL)
      T->root = v;
   else if(u == u->parent->left)
      u->parent->left = v;
   else 
      u->parent->right = v;
   v->parent = u->parent;
}
 
void RB_DeleteFixUp(Dictionary T, Node x)
{
	Node w;
   while(x != T->root && x->color == BLACK)
   {
      if(x == x->parent->left)
	  {
         w = x->parent->right;
         if(w->color == RED)
		 {
            w->color = BLACK;                        // case 1
            x->parent->color = RED;                   // case 1
            LeftRotate(T, x->parent);                // case 1
            w = x->parent->right;                     // case 1
		 }
         if(w->left->color == BLACK && w->right->color == BLACK)
		 {
            w->color = RED;                          // case 2
            x = x->parent;                           // case 2
		 }
         else 
		 {
            if(w->right->color == BLACK)
			{
               w->left->color = BLACK;                // case 3
               w->color = RED;                       // case 3
               RightRotate(T, w);                   // case 3
               w = x->parent->right;                  // case 3
			}
            w->color = x->parent->color;               // case 4
            x->parent->color = BLACK;                 // case 4
            w->right->color = BLACK;                  // case 4
            LeftRotate(T, x->parent);                // case 4
            x = T->root;                             // case 4
		 }
	  }
      else 
	  {
         w = x->parent->left;
         if(w->color == RED)
		 {
            w->color = BLACK;                        // case 5
            x->parent->color = RED;                   // case 5
            RightRotate(T, x->parent);               // case 5
            w = x->parent->left;                      // case 5
		 }
         if(w->right->color == BLACK && w->left->color == BLACK)
		 {
            w->color = RED;                          // case 6
            x = x->parent;                           // case 6
		 }
         else 
		 {
            if(w->left->color == BLACK)
			{
               w->right->color = BLACK;               // case 7
               w->color = RED;                       // case 7
               LeftRotate(T, w);                    // case 7
               w = x->parent->left;                   // case 7
			}
            w->color = x->parent->color;               // case 8
            x->parent->color = BLACK;                 // case 8
            w->left->color = BLACK;                   // case 8
            RightRotate(T, x->parent);               // case 8
            x = T->root;                             // case 8
		 }
	  }
   }
   x->color = BLACK;
}   
// Constructors-Destructors ---------------------------------------------------

// newDictionary()
// Constructor for the Dictionary type.
Dictionary newDictionary(int unique)
{
   Dictionary D = malloc(sizeof(DictionaryObj));
   D->root = NIL;
   D->numPairs = 0;
   D->unique = unique;
   D->cursor = NIL;
   return D;
}

// freeDictionary()
// Destructor for the Dictionary type.
void freeDictionary(Dictionary* pD){
   if( pD!=NULL && *pD!=NULL )
   {
      makeEmpty(*pD);
      free(*pD);
      *pD = NULL;
   }
}


// ADT operations -------------------------------------------------------------

// size()
// Return the number of (key, value) pairs in Dictionary D.
int size(Dictionary D)
{
   if( D==NULL )
   {
      fprintf(stderr, 
         "Dictionary Error: calling size() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }

   return D->numPairs;
}

// getUnique()
// Returns true (1) if D requires that all pairs have unique keys. Returns
// false (0) if D accepts distinct pairs with identical keys.
int getUnique(Dictionary D)
{
	if(D->unique == 0)
		return 0;
	else
		return 1;
}

// lookup()
// If Dictionary D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
// returns VAL_UNDEF.
VAL_TYPE lookup(Dictionary D, KEY_TYPE k){
	Node N = NIL;
	if( D==NULL ){
	  fprintf(stderr, 
		 "Dictionary Error: calling lookup() on NULL Dictionary reference\n");
	  exit(EXIT_FAILURE);
	}
	N = findKey(D->root, k);
	if(N == NIL)
		return VAL_UNDEF;
	return (N->value);
}

// Manipulation procedures ----------------------------------------------------

// insert()
// Insert the pair (k,v) into Dictionary D. 
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced. 
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v)
{
	Node N,B,A;
	if( D==NULL )
	{
	  fprintf(stderr, 
		 "Dictionary Error: calling insert() on NULL Dictionary reference\n");
	  exit(EXIT_FAILURE);
	}
	// if(getUnique(D) == 1)
	// {
		// if( findValue(D->root, k)!= VAL_UNDEF )
		// {
		  // fprintf(stderr, 
			 // "Dictionary Error: cannot insert() duplicate key: \"%s\"\n", k);
		  // exit(EXIT_FAILURE);
		// }
	// }
	N = newNode(k,v);
	B = NIL;
	A = D->root;
	while(A != NIL)
	{
		B = A;
		if(strcmp(k, A->key)<0)
			A = A->left;
		else 
			A = A->right;
	}
	N->parent = B;
	if(B == NIL)
		D->root = N;
	else if( strcmp(k, B->key)<0 )
		B->left = N;
	else 
		B->right = N;
	//N->left = NIL;
	//N->right = NIL;
	N->color = RED;
	// fprintf(stdout,"before: key is %s, parent is %s, left child is %s, right child is %s, color is %d\n",z->key, z->parent->key, z->left->key, z->right->key, z->color);
	RB_InsertFixUp(D, N);
	D->numPairs++;
	//fprintf(stdout,"after:  key is %s, parent is %s, left child is %s, right child is %s, color is %d\n",z->key, z->parent->key, z->left->key, z->right->key, z->color);
	//fprintf(stdout, "\n");
	
}

// delete()
// Remove pair whose first member is the argument k from D.
// Pre: lookup(D,k)!=NULL (D contains a pair whose first member is k.)
void delete(Dictionary D, KEY_TYPE k)
{
	Node x, y, z;
	z = findKey(D->root, k);
	y = z;
	int y_original_color = y->color;
	if(z == D->cursor)
   {
	   D->cursor = NIL;
   }
   
	if(z->left == NIL)
	{
		x = z->right;
		RB_Transplant(D, z, z->right);
	}
	else if(z->right == NIL)
	{
		x = z->left;
		RB_Transplant(D, z, z->left);
	}
	else 
	{
		y = findLeftmost(z->right);
		y_original_color = y->color;
		x = y->right;
		if(y->parent == z)
			x->parent = y;
		else 
		{
			RB_Transplant(D, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		RB_Transplant(D, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if(y_original_color == BLACK)
		RB_DeleteFixUp(D, x);
	D->numPairs--;
	//fprintf(stdout,"cursor is at %s\n",D->cursor->key);
}

// makeEmpty()
// Reset D to the empty state, the empty set of pairs.
void makeEmpty(Dictionary D){
   if( D==NULL ){
      fprintf(stderr, 
         "Dictionary Error: calling makeEmpty() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }

   deleteAll(D->root);
   D->root = NIL;
   D->numPairs = 0;
   D->cursor = NIL;
}

// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key 
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF. 
VAL_TYPE beginForward(Dictionary D)
{
	Node N = D->root;
	if(D == NULL){
		fprintf(stderr, "Dictionary Error: calling beginForward() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	if(size(D) == 0)
	{
		return VAL_UNDEF;
	}
	N = findLeftmost(N);
	//fprintf(stdout, "N value is: %i\n",N->value);
	//fprintf(stdout, "key is: %s\n",N->key);
	D->cursor = N;
	//fprintf(stdout,"D->value is %i, D->key is %s\n",D->cursor->value, D->cursor->key);
	return N->value;
}

// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key 
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Dictionary D)
{
	Node N = D->root;
	if(D == NULL){
		fprintf(stderr, "Dictionary Error: calling beginForward() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	if(size(D) == 0)
	{
		return VAL_UNDEF;
	}
	N = findRightmost(N);
	//fprintf(stdout, "N value is: %i\n",N->value);
	//fprintf(stdout, "key is: %s\n",N->key);
	D->cursor = N;
	//fprintf(stdout,"D->value is %i, D->key is %s\n",D->cursor->value, D->cursor->key);
	return N->value;
}

// currentKey()
// If an iteration (forward or reverse) over D has started, returns 
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D)
{
	if(D == NULL){
		fprintf(stderr, "Dictionary Error: calling currentKey() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	//fprintf(stdout,"cursor key is %s\n",D->cursor->key);
	return D->cursor->key;
}

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the 
// value corresponding to the current key. If no iteration is underway, 
// returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D)
{
	if(D == NULL){
		fprintf(stderr, "Dictionary Error: calling currentVal() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	//fprintf(stdout,"cursor value is %i\n",D->cursor->value);
	return D->cursor->value;
}

// next()
// If an iteration (forward or reverse) over D has started, and has not
// reached the last pair, moves to the next key in D (as defined by the 
// order operator KEY_CMP()), and returns the value corresponding to the 
// new key. If an iteration has started, and has reached the last pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
// returns VAL_UNDEF.
VAL_TYPE next(Dictionary D)
{
	if(D == NULL){
		fprintf(stderr, "Dictionary Error: calling next() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	if(D->cursor == NIL)
	{
		return VAL_UNDEF;
	}
	Node N = D->cursor;
	//fprintf(stdout,"key is %s\n", N->key);
	Node N1 = TreeSuccessor(N);
	D->cursor = N1;
	//fprintf(stdout,"successor cursor key is %s cursor parent key is %s\n",N1->key, N1->parent->key);
	//fprintf(stdout,"next key is %s\n", N1->key);
	return N1->value;
}

// prev()
// If an iteration (forward or reverse) over D has started, and has not
// reached the first pair, moves to the previous key in D (as defined by the 
// order operator KEY_CMP()), and returns the value corresponding to the 
// new key. If an iteration has started, and has reached the first pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
// returns VAL_UNDEF. 
VAL_TYPE prev(Dictionary D)
{
	if(D == NULL){
		fprintf(stderr, "Dictionary Error: calling next() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	if(D->cursor == NIL)
	{
		return VAL_UNDEF;
	}
	Node N = D->cursor;
	Node N1 = TreePredecessor(N);
	D->cursor = N1;
	//fprintf(stdout,"current key is %s cursor parent key is %s\n",N1->key, N1->parent->key);
	return N1->value;
}
// Other Operations -----------------------------------------------------------

// toStringInOrder()
// Uses an in-order traversal of the subtree rooted at R to copy the pairs in
// that subtree, including a separating space and newline for each pair, to the
// char array pointed to by buf, and ending with a terminating null '\0' 
// character. Returns a pointer to the terminating null. Used by function 
// printDictionary().
void inOrderTreeWalk(FILE* out, Node R)
{
   if( R->key != KEY_UNDEF )
   {
      inOrderTreeWalk(out, R->left);
	  fprintf(out,"%s", R->key);
	  //fprintf(stdout,"before: key is %s, parent is %s, left child is %s, right child is %s, color is %d\n",R->key, R->parent->key, R->left->key, R->right->key, R->color);
      inOrderTreeWalk(out, R->right);
   }
}

void postOrderTreeWalk(FILE* out, Node R)
{
   if( R->key != KEY_UNDEF )
   {
      postOrderTreeWalk(out, R->left);	  
      postOrderTreeWalk(out, R->right);
	  fprintf(out,"%s", R->key);
   }
}
void preOrderTreeWalk(FILE* out, Node R)
{
   if( R->key != KEY_UNDEF )
   {
	  fprintf(out,"%s", R->key);
      preOrderTreeWalk(out, R->left);  
      preOrderTreeWalk(out, R->right);
   }
}

// printDictionary()
// Prints a text representation of D to the file pointed to by out. Each key-
// value pair is printed on a single line, with the two items separated by a
// single space.  The pairs are printed in the order defined by the operator
// KEY_CMP().
void printDictionary(FILE* out, Dictionary D, const char* ord)
{
   if( D==NULL ){
      fprintf(stderr, 
         "Dictionary Error: calling DictionaryToString() on NULL Dictionary "\
         "reference\n");
      exit(EXIT_FAILURE);
   }
	//fprintf(stdout,"cursor is on %s\n", D->cursor->key);
	//inOrderTreeWalk(out, D->root);
	//fprintf(stdout, "size of dictionary is %i\n",size(D));
	if(strcmp(ord,"in") == 0)
		inOrderTreeWalk(out, D->root);
	else if(strcmp(ord,"pre") == 0)
		preOrderTreeWalk(out, D->root);
	else if(strcmp(ord,"post") == 0)
		postOrderTreeWalk(out, D->root);
	else
		fprintf(stdout, "order is not in, pre, or post\n");//do nothing
}