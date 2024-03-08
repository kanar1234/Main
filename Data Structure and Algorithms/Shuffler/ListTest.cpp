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

int main(){
	List A, B, C, D;
	
	//clear test
	A.insertAfter(1);
	A.insertAfter(2);
	A.insertAfter(3);
	A.insertBefore(5);
	A.insertBefore(12);
	//A.clear();
	cout << "A.size() = " << A.size() << endl;
	cout << "A.position() = " << A.position() << endl;
	
	//concat equals test
	A.insertBefore(1);
	A.insertAfter(3);
	A.insertAfter(2);
	B.insertBefore(3);
	B.insertBefore(2);
	B.insertBefore(1);
	C.insertAfter(1);
	C.insertAfter(2);
	C.insertAfter(3);
	C.insertAfter(3);
	C.insertAfter(2);
	C.insertAfter(1);
	cout << "A = " << A << endl;
	cout << "B = " << B << endl;
	cout << "C = " << C << endl;
	cout << "C.position() = " << C.position() << endl;
	cout << "C.peekNext() = " << C.peekNext() << endl;
	cout << "C.peekPrev() = " << C.peekPrev() << endl;
	cout << "C.size() = " << C.size() << endl;
	cout << "-------------------------" << endl;
	cout << "C = A and B? = " << C.equals(A.concat(B)) << endl;
	cout << "C = D? = " << C.equals(D) << endl;
	cout << "D.position() = " << D.position() << endl;
	cout << "D.peekNext() = " << D.peekNext() << endl;
	cout << "D.peekPrev() = " << D.peekPrev() << endl;
	cout << "D.size() = " << D.size() << endl;
	
	//cleanup test
	A.insertBefore(1);
	A.insertBefore(2);
	A.insertBefore(2);
	A.insertBefore(1);
	A.insertBefore(2);
	A.insertBefore(3);
	A.insertBefore(1);
	A.findPrev(3);
	A.cleanup();
	
	cout << "A = " << A << endl;
	cout << "A.position() = " << A.position() << endl;
	cout << "A.peekNext() = " << A.peekNext() << endl;
	cout << "A.peekPrev() = " << A.peekPrev() << endl;
	cout << "A.size() = " << A.size() << endl;
	
	B.insertBefore(1);
	B.insertBefore(2);
	B.insertBefore(2);
	B.insertBefore(1);
	B.insertBefore(2);
	B.insertBefore(3);
	B.insertBefore(1);
	B.findPrev(3);
	B.movePrev();
	B.cleanup();
	
	cout << "B = " << B << endl;
	cout << "B.position() = " << B.position() << endl;
	cout << "B.peekNext() = " << B.peekNext() << endl;
	cout << "B.peekPrev() = " << B.peekPrev() << endl;
	cout << "B.size() = " << B.size() << endl;
	
	//find next test
	A.insertAfter(77);
	A.insertAfter(55);
	A.insertAfter(1);
	A.insertAfter(34);
	A.insertAfter(1);
	A.insertAfter(77);
	A.insertAfter(77);
	A.insertAfter(34);
	cout << "A = " << A << endl;
	cout << "A.findNext(99) = " << A.findNext(99) << endl;
	cout << "A.position() = " << A.position() << endl;
	cout << "A.peekNext() = " << A.peekNext() << endl;
	cout << "A.peekPrev() = " << A.peekPrev() << endl;
	cout << "A.size() = " << A.size() << endl;
	
	A.moveFront();
	cout << "A = " << A << endl;
	cout << "A.findNext(1) = " << A.findNext(1) << endl;
	cout << "A.position() = " << A.position() << endl;
	cout << "A.peekNext() = " << A.peekNext() << endl;
	cout << "A.peekPrev() = " << A.peekPrev() << endl;
	cout << "A.size() = " << A.size() << endl;
	
	//moveNext value test
	
	A.insertAfter(3215);
	A.insertAfter(176);
	A.insertAfter(22);
	A.insertAfter(5);
	A.insertAfter(1);
	A.moveNext();
	
	cout << "-------------------------" << endl;
	cout << "A = " << A << endl;
	cout << "A.peekNext() = " << A.peekNext() << endl;
	cout << "A.peekPrev() = " << A.peekPrev() << endl;
	cout << "A.position() = " << A.position() << endl;
	cout << "A.moveNext() = " << A.moveNext() << endl;
	cout << "A.size() = " << A.size() << endl;
	
	A.eraseBefore(); 
	A.eraseBefore();
	cout << "-------------------------" << endl;
	cout << "A2 = " << A << endl;
	cout << "A.peekNext() = " << A.peekNext() << endl;
	cout << "A.peekPrev() = " << A.peekPrev() << endl;
	cout << "A.position() = " << A.position() << endl;
	cout << "A.size() = " << A.size() << endl;
	cout << "-------------------------" << endl;
	
	A.moveNext();
	A.moveNext();
	A.moveNext();
		
	cout << "A = " << A << endl;
	cout << "A.peekNext() = " << A.peekNext() << endl;
	cout << "A.peekPrev() = " << A.peekPrev() << endl;	
	cout << "A.position() = " << A.position() << endl;
	cout << "A.size() = " << A.size() << endl;
	cout << "-------------------------" << endl;
	
	//concatposition test

	A.insertBefore(1);
	A.insertBefore(2);
	A.insertBefore(3);
	B.insertBefore(4);
	B.insertBefore(5);
	B.insertBefore(6);
	C = A.concat(B);
	cout << "C = " << C << endl;
	cout << "C.position() = " << C.position() << endl;
	cout << "C.size() = " << C.size() << endl;
	
	//concatsize test 
	A.insertAfter(1);
	A.insertAfter(2);
	A.insertAfter(3);
	B.insertAfter(4);
	B.insertAfter(5);
	B.insertAfter(6);
	C = A.concat(B);
	cout << "A = " << A << endl;
	cout << "B = " << B << endl;
	cout << "C = " << C << endl;
	//erasebefore test
	A.insertAfter(1);
    A.insertAfter(2);
    A.insertAfter(3);
    A.insertAfter(5);
    A.insertAfter(12);
	A.movePrev();
	A.eraseBefore();
	if (A.size() != 4) return 1;
	A.findPrev(2);
	
	//eraseafter test
	A.insertBefore(1);
	A.insertBefore(2);
	A.insertBefore(3);
	A.insertBefore(5);
	A.insertBefore(12);
	
	A.movePrev();
	A.eraseAfter();
	A.findPrev(2);
	cout << "A = " << A << endl;
	cout << "A.position() = " << A.position() << endl;
	cout << "A.size() = " << A.size() << endl;
	
	A.eraseAfter();
	
	cout << "A = " << A << endl;
	cout << "A.position() = " << A.position() << endl;
	cout << "A.size() = " << A.size() << endl;
	
	A.findPrev(2);
	
	cout << "A = " << A << endl;
	cout << "A.position() = " << A.position() << endl;
	cout << "A.size() = " << A.size() << endl;
	
	
	A.eraseAfter();
	
	
	
	cout << "A.findNext(5) = " << A.findNext(5) << endl; 
	cout << "A.position() after findnext= " << A.position() << endl;
	cout << "A.size() = " << A.size() << endl; 
	cout << "A = " << A << endl;
	return(0);
}