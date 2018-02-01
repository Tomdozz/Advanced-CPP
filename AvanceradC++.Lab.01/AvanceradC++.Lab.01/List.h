#pragma once
#include "Link.h"
#include <iostream>
#include <assert.h>
using namespace std;
template<class T>
class List :public Link<T>
{
public:
	List();
	T* First();			   
	T* Last();			   
	T* PushFront(T* item); 
	T* PopFront();		   
	T* PushBack(T* item); 
	template<class arg>
	T* FindFirst(const arg& searchFor) { return FindNext(searchFor); }
	friend std::ostream& operator<<(std::ostream& cout, List& list)
	{
		return list.Print(cout);
	}
	bool IsEmpty();
	void Check();
	//~List();

	bool Invariant()
	{
		//return next->prev == prev->next; //&& next->prev == NULL && prev->next == NULL;
		return next->prev == this && prev->next == this || next->prev == NULL && prev->next == NULL;
	}
private:
	std::ostream& Print(std::ostream& cout);
};

template<class T>
List<T>::List()
{
	next = this;
	prev = this;
}

template<class T>
T * List<T>::First()
{
	return dynamic_cast<T*>(next);
}

template<class T>
T *	List<T>::Last()
{
	return dynamic_cast<T*>(prev);
}

template<class T>
T * List<T>::PushFront(T * item)
{
	if (IsEmpty())
	{
		next = item;
		prev = item;
	}
	else
	{
		item->next = next;
		next->prev = item;
		next = item;
	}
	cout << "sucessfully added front" << endl;
	return item;
}

template<class T>
T * List<T>::PopFront()
{
	if (IsEmpty())
	{
		cout << "nothing to pop" << endl;
		return NULL;
	}
	if (next->next == NULL)
	{
		T* removedNode = dynamic_cast<T*>(next);
		next = this;
		prev = this;
		return removedNode;
	}
	return DeleteAfter();
}

template<class T>
T * List<T>::PushBack(T * item)
{
	if (IsEmpty())
	{
		next = item;
		prev = item;
	}
	else
	{
		item->prev = prev;
		prev->next = item;
		prev = item;
	}
	cout << "sucessfully added back" << endl;
	return item;
}

template<class T>
bool List<T>::IsEmpty()
{
	return (next == this && prev == this);
}

template<class T>
void List<T>::Check()
{
	const Link<T>*node = this, *nextNode = next;
	do {
		assert(node->next == nextNode && nextNode->prev == node);
		node = nextNode;
		nextNode = nextNode->next;
	} while (node != this);
}

template<class T>
std::ostream & List<T>::Print(std::ostream & cout)
{
	for (Node* item = First(); item != nullptr; item = item->Next())
	{
		dynamic_cast<T*>(item)->Print(cout);
	}
	return cout;
}
