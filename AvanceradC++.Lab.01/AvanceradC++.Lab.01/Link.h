#pragma once
//link to TheChernoProject explanation of templates
//https://www.youtube.com/watch?v=I-hZkUa9mIs
//dynamic_cast is done in runtime
//static_cast is done in compiletime

#include <iostream>
#include <assert.h>

template<class T>
class List;

template<class T>
class Link
{
	Link* next;
	Link* prev;
	friend class List<T>;

public:
	Link();
	virtual ~Link() = default;
	T* Next();				
	T* Prev();				
	const T* Next()const;
	const T* Prev()const;

	T* InsertAfter(T* TToInsert);
	T* InsertBefor(T* TToInsert);
	T* DeleteAfter();
	template<class arg>
	T* FindNext(const arg& searchFor);

	virtual std::ostream& Print(std::ostream& cout) { 	return cout;	}

	bool Invariant()
	{
		return next->prev == this && prev->next == this || next == NULL && prev == NULL;
	}
};

template<class T>
inline Link<T>::Link() :next(nullptr), prev(nullptr) {}

template<class T>
T * Link<T>::Next()
{
	return dynamic_cast<T*>(next);
}

template<class T>
T *	Link<T>::Prev()
{
	return dynamic_cast<T*>(prev);
}

template<class T>
const T * Link<T>::Next() const
{
	return dynamic_cast<T*>(next);
}

template<class T>
const T * Link<T>::Prev() const
{
	return dynamic_cast<T*>(prev);
}

//exempel insertafter i link.h
//
//T* InsertAfter(T* TToInsert)
//{
//	assert(Invariant());
//	TToInsert->next = next;
//	TToInsert->prev = this;
//	if (next != nullptr)
//		next->prev = TToInsert;
//	next = TToInsert;
//	assert(Invariant());
//	return TToInsert;
//};

template<class T>
T * Link<T>::InsertAfter(T * TToInsert)
{
	assert(Invariant());
	TToInsert->next = next;
	TToInsert->prev = this;
	if (next != nullptr)
	{
		next->prev = TToInsert;
	}

	next = TToInsert;
	assert(Invariant());
	return TToInsert;
}

template<class T>
T * Link<T>::InsertBefor(T * TToInsert)
{
	assert(Invariant());
	TToInsert->prev = prev;
	TToInsert->next = this;
	if (prev != nullptr)
	{
		prev->next = TToInsert;
	}
	prev = TToInsert;
	assert(Invariant());
	return TToInsert;
}

template<class T>
T* Link<T>::DeleteAfter()
{
	if (next == nullptr)
	{
		cout << "nothing to delete" << endl;
		return nullptr;
	}
	else
	{
		T* removedNode = dynamic_cast<T*>(next);
		next = next->next;
		next->prev = this;
		return removedNode;
	}
}
template<class T>
template<class arg>
T * Link<T>::FindNext(const arg & searchFor)
{
	//recursivly tries to find what we are searching for
	if (next == nullptr)
	{
		return nullptr;
	}
	if (dynamic_cast<T*>(next)->Match(searchFor))
	{
		//return (T*)(next)->Match(searchFor);
		return dynamic_cast<T*>(next);
	}
	else
		next->FindNext(searchFor);
}