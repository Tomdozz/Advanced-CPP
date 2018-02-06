#pragma once
#include <iostream>
#include <memory.h>
#include "StringItt.h"

class String
{
	char* cString;
	int length;			
	int holds;			
public:
	typedef StringItt<char>::iterator iterator;
	typedef StringItt<char>::reverse_iterator reverse_iterator;
	iterator begin() { return iterator(cString); }
	iterator end() { return iterator(cString+holds); }
	reverse_iterator rbegin() { return reverse_iterator(&cString[holds-1]); }
	reverse_iterator rend() { return reverse_iterator(&cString[0]-1); }

	String();
	String(const String& rhs);
	String(const char* cstr);
	String& operator=(const String& rhs);
	String& operator+=(const String& rhs);
	String operator+();
	explicit operator bool();
	
	int capacity() const;
	int size()const;
	bool isEmpty();
	bool Invariant() const {
		/*if (cString == nullptr)
			return false;
		else {
			return  0 <= holds && holds <= length && cString[holds] == '\0';
		}*/
		return true;
	}
	char& at(size_t i);
	char& operator[](int i);
	const char& operator[](int i) const;
	const char* data() const;
	void reserve(size_t n);
	void shrink_to_fit();
	void push_back(char c);
	void resize(size_t n);
	friend bool operator==(const String& lhs, const String& rhs);
	friend bool operator!=(const String& lhs, const String& rhs);
	friend std::ostream& operator<<(std::ostream& cout, String& rhs) {
		for (size_t i = 0; i < rhs.size(); ++i) {
			cout << rhs.cString[i];
		}
		return cout;
	}
	~String() { cString = nullptr; }
};

