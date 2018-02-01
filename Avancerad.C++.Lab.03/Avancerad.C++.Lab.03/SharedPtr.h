#pragma once
#include <cassert>
template<class T>
class ControlBlock
{
	int count = 0;
public:
	T* actualObject;
	ControlBlock(T* obj) :actualObject(obj), count(1) {}
	ControlBlock() : actualObject(nullptr), count(1) {}
	T* getActualObj() { return actualObject; }
	int getCount() { return count; }
	void add() { count++; }
	void remove() { count--; }
	~ControlBlock()
	{
		delete actualObject;
		actualObject = nullptr;
	}
private:
};
template<class T>
class SharedPtr
{
	ControlBlock<T>* m_controller;
public:
	SharedPtr();
	SharedPtr(T* realPtr);
	SharedPtr(const SharedPtr& rhs);
	SharedPtr(SharedPtr&& rhs);
	SharedPtr& operator=(SharedPtr<T>&);
	bool operator==(const SharedPtr& rhs) const;
	bool operator<(const SharedPtr<T>& rhs);
	void Reset(T* ptr = nullptr);
	bool Unique();
	void Release();
	operator bool();
	T& operator*() const { return *get(); }
	T* operator->() const { return m_controller->getActualObj(); }
	T* get() const { return m_controller->getActualObj(); }
	bool Invariant() { return m_controller == nullptr || m_controller->getCount() > 0; }
	~SharedPtr() { Reset(); }
};

template<class T>
SharedPtr<T>::SharedPtr() : m_controller(new ControlBlock<T>()) {}

template<class T>
SharedPtr<T>::SharedPtr(T * realPtr) : m_controller(new ControlBlock<T>(realPtr)) {}

template<class T>
SharedPtr<T>::SharedPtr(const SharedPtr & rhs) : m_controller(rhs.m_controller) { m_controller->add(); }

template<class T>
SharedPtr<T>::SharedPtr(SharedPtr && rhs) : m_controller(rhs.m_controller) { m_controller->add(); rhs.Reset(); }

template<class T>
bool SharedPtr<T>::operator==(const SharedPtr& rhs) const { return get() == rhs.get() ? true : false; }

template<class T>
inline SharedPtr<T>::operator bool() { return m_controller == nullptr || get() == nullptr ? false : true; }

template<class T>
void SharedPtr<T>::Reset(T* ptr = nullptr)
{
	assert(Invariant());
	if (m_controller != nullptr) {
		if (m_controller->getCount() == 1) {
			delete m_controller;
			m_controller = nullptr;
		}
		else {
			m_controller->remove();
			m_controller = nullptr;
		}
	}
	assert(Invariant());
}

template<class T>
inline void SharedPtr<T>::Release()
{
	assert(Invariant());
	T* old = m_controller;
	m_controller = 0;
	assert(Invariant());
	return old;
}

template<class T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>& rhs)
{
	assert(Invariant());
	if (m_controller != rhs.m_controller) {
		Reset();
		rhs.m_controller->add();
		m_controller = rhs.m_controller;
	}
	assert(Invariant());
	return *this;
}

template<class T>
bool SharedPtr<T>::Unique()
{
	assert(Invariant());
	return m_controller->getCount() <= 1 ? true : false;
}

template<class T>
inline bool SharedPtr<T>::operator<(const SharedPtr<T>& rhs)
{
	assert(Invariant());
	return get() < rhs.get() ? true : false;
}