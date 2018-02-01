#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

template <typename T>
class StringItt :public std::iterator<std::random_iterator_tag, T>
{
public:
	typedef int size_type;

	class iterator
	{
	public:
		typedef iterator selfType;
		typedef T valueType;
		typedef T& reference;
		typedef T* pointer;
		typedef std::random_access_iterator_tag iteratorCatrgory;
		typedef int differntType;
		bool invariant() { return ptr != nullptr; }

		iterator() = default;
		iterator(pointer ptr) : ptr(ptr) {}
		iterator(iterator & rhs) {}
		iterator& operator=(const iterator& rhs)
		{
			ptr = rhs.ptr;
			return *this;
		}
		reference operator*() { return *ptr; }
		pointer operator->() { return ptr; }
		bool operator==(const selfType& rhs) { return ptr == rhs.ptr; }
		bool operator!=(const selfType& rhs) { return ptr != rhs.ptr; }
		reference operator[](int i) { return *(ptr + i); } //from ptr go i step forward.
		selfType operator+(const int& rhs)
		{
			assert(invariant());
			pointer temp = ptr;
			return iterator(temp += rhs);
		}
		//pre-incremental
		selfType operator++()
		{
			assert(invariant());
			++ptr;
			return iterator(ptr);
		}
		//post-incremental
		selfType operator++(int)
		{
			assert(invariant());
			pointer temp = ptr;
			++ptr;
			return iterator(temp);
		}
		selfType operator--(int)
		{
			assert(invariant());
			pointer temp = ptr;
			--ptr;
			return iterator(temp);
		}
		pointer operator--()
		{
			assert(invariant());
			--ptr;
			return iterator(ptr);
		}

	private:
		pointer ptr;
	};

	class reverse_iterator
	{
	public:
		typedef reverse_iterator selfType; //just so we dont have to write iterator all the time 
		typedef T valueType;
		typedef T& reference;
		typedef T* pointer;
		typedef std::random_access_iterator_tag iteratorCatrgory;
		typedef int differntType;
		bool invariant() { return ptr != nullptr; }

		reverse_iterator() = default;
		reverse_iterator(pointer ptr) : ptr(ptr) {}
		reverse_iterator(reverse_iterator & rhs) {}
		reverse_iterator& operator=(const reverse_iterator& rhs)
		{
			assert(invariant());
			ptr = rhs.ptr;
			return *this;
		}
		reference operator[](int i) { return *(ptr - i); } //from ptr go i step forward.
		selfType operator+(const int& rhs)
		{
			assert(invariant());
			pointer temp = ptr;
			return reverse_iterator(temp -= rhs);
		}
		//pre-incremental
		selfType operator++()
		{
			assert(invariant());
			--ptr;
			return reverse_iterator(ptr);
		}
		//post-incremental
		selfType operator++(int)
		{
			assert(invariant());
			pointer temp = ptr;
			--ptr;
			return reverse_iterator(temp);
		}
		selfType operator--(int)
		{
			assert(invariant());
			pointer temp = ptr;
			++ptr;
			return reverse_iterator(temp);
		}
		pointer operator--()
		{
			assert(invariant());
			++ptr;
			return reverse_iterator(ptr);
		}
		reference operator*() { return *ptr; }
		pointer operator->() { return ptr; }
		bool operator==(const selfType& rhs) { return ptr == rhs.ptr; }
		bool operator!=(const selfType& rhs) { return ptr != rhs.ptr; }

	private:
		pointer ptr;
	};

	StringItt(size_type size) : size(size) { data = new T[size]; }
	StringItt(StringItt& rhs) {}
	StringItt& operatro = (const reverse_iterator& rhs) {}
	size_type size() { return size; }
	T& opearetor[](size_type index)
	{
		assert(index > size);
		return data[index];
	}
	const T& operator[](size_type index)
	{
		assert(index > size);
		return data[index];
	}
	Iterator begin()
	{
		return Iterator(data);
	}
	Iterator end()
	{
		return Iterator(data + size);
	}
private:
	size_type size;
	T* data;
};