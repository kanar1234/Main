//-----------------------------------------------------------------------------
// Alan Szeto
// 1672580
// pa7
// ListTest.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include"List.h"

using namespace std;

void shuffle(List& D)
{
	
	List A;
	D.moveFront();
	for(int i = 0; i < D.size()-1; i++)
	{
		A.insertBefore(D.peekNext());
		D.eraseAfter();
	}
	D.moveFront();
	A.moveFront();
	//cout << "A is " << A << endl;
	while(A.size() > 0)
	{
		D.moveNext();
		D.insertBefore(A.peekNext());
		A.eraseAfter();
	}
	D.moveFront();
	// cout << "A is " << A << endl;
	// cout << "A.size() is " << A.size() << endl;
	// cout << "D.position() = " << D.position() << endl;
	// cout << "D.peekNext() = " << D.peekNext() << endl;
	// cout << "D.peekPrev() = " << D.peekPrev() << endl;
}

int main(int argc, char *argv[]){
	List L, L2;
	int shuf = std::stoi(argv[1]);
	int count = 0;
	
	cout << "deck size       shuffle count" << endl;
	cout << "------------------------------" << endl;
	for (int i = 1; i < shuf+1; i++) 
	{
		L.insertBefore(i);	
		L2 = L;
		shuffle(L);
		while(!L2.equals(L))
		{
			shuffle(L);
			count++;
		}	
		count++;
		cout << " " << L.size() << "               " << count << endl;
		count = 0;
	}
	
	return(0);
}

