// AvanceradC++.Lab.01.cpp : Defines the entry point for the console application.
//

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include "stdafx.h"
#include <iostream>
#include "List.h"
#include "Link.h"
#include <assert.h>

using namespace std;
#define LOG(x) cout<<x<<endl;

class Node :public Link<Node> {
public:
	float data;
	Node(float v = 0) :data(v) {}
	bool Match(float v) { return data == v; }
	virtual std::ostream& Print(std::ostream& cout) const {
		return cout << data;
	}
};

void TestDLL();
template Link<Node>;    //Detta tvingar fram att allting i Link kompileras
template List<Node>;    //Detta tvingar fram att allting i List kompileras


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	TestDLL();
	cin.get();
	return 0;
}


void TestDLL()
{
	List<Node> myList;
	assert(myList.Invariant());
	Node * nodeA3 = myList.PushFront(new Node(3));
	assert(myList.Invariant());
	myList.PushFront(new Node(2));
	myList.PushFront(new Node(1));
	assert(myList.Invariant());
	myList.PushBack(new Node(1));
	myList.PushBack(new Node(2));
	myList.PushBack(new Node(3));
	//myList.Check();
	assert(myList.Invariant());
	assert(myList.Last()->Next() == nullptr);
	//std::cout << myList;    //should be 1 2 3 1 2 3
	std::cout << myList << endl;

	Node * tempA3 = myList.FindNext(3);
	assert(tempA3 == nodeA3);
	Node * nodeB1 = nodeA3->FindNext(1);
	Node * tempB1 = tempA3->DeleteAfter();   //ta bort andra 1:an
	assert(myList.Invariant());
	assert(tempB1->data == 1);

	Node * nodeA2 = myList.FindFirst(2);
	Node * nodeB2 = nodeA2->FindNext(2);
	Node * temp = nodeB2->FindNext(2);
	assert(!temp);

	nodeA2->DeleteAfter();
	//std::cout << myList;    //1 2 2 3
	std::cout << myList << endl;

	myList.First()->Next()->InsertAfter(tempA3)->InsertAfter(tempB1);
	assert(myList.Last()->Prev()->data == 2);
	assert(myList.Invariant());
	//std::cout << myList;    //should be 1 2 3 1 2 3
	std::cout << myList << endl;
	{Node* t = myList.PopFront(); assert(t->data == 1); delete t; }
	{Node* t = myList.PopFront(); assert(t->data == 2); delete t; }
	{Node* t = myList.PopFront(); assert(t->data == 3); delete t; }
	{Node* t = myList.PopFront(); assert(t->data == 1); delete t; }
	{Node* t = myList.PopFront(); assert(t->data == 2); delete t; }
	{Node* t = myList.PopFront(); assert(t->data == 3); delete t; }
	assert(myList.PopFront() == nullptr);
	assert(myList.PopFront() == nullptr);
	std::cout << myList << "end";
	assert(myList.Invariant());
	std::cin.get();
}


