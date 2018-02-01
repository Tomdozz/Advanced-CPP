#include "stdafx.h"
#include "String.h"
#include "memory.h"
#include <iostream>
#include <utility>  
#include <cassert>
using namespace std;
String::String() : cString(""), holds(0), length(0) {}

String::String(const String& rhs) : holds(rhs.holds), length(rhs.length)
{
	cString = new char[rhs.capacity()+1];
	for (size_t i = 0; i < holds + 1; i++) {
		cString[i] = rhs.cString[i];
	}
	cString[holds] = 0;
	assert(Invariant());
}

String::String(const char* cstr)
{
	length = strlen(cstr);
	holds = strlen(cstr);
	cString = new char[holds];
	for (size_t i = 0; i < holds + 1; i++) {
		cString[i] = cstr[i];
	}
	cString[holds] = 0;
	assert(Invariant());
}
String::operator bool() { return (holds > 0); }
bool String::isEmpty() { return (holds == 0); }
int String::capacity() const { return length; }
int String::size() const { return holds; }
const char * String::data() const { return cString; }
char& String::operator[](int i) { return cString[i]; }
const char& String::operator[](int i) const { return cString[i]; }
//const char String::begin() { return cString[0]; }
//const char String::end() { return cString[holds + 1]; }
//const char String::rbegin() { return cString[holds + 1]; }
//const char String::rend() { return cString[0]; }

String & String::operator=(const String & rhs)
{
	assert(Invariant());
	if (size() < rhs.size())
	{
		char* temp = new char[rhs.size()];
		for (size_t i = 0; i < rhs.size(); i++) {
			temp[i] = rhs.cString[i];
		}
		cString = temp;
		delete[] temp;

	}
	else if (size() > rhs.size())
	{
		for (size_t i = 0; i < rhs.size(); i++) {
			cString[i] = rhs.cString[i];
		}
	}
	else if (size() == rhs.size())
	{
		for (size_t i = 0; i < rhs.size(); i++) {
			cString[i] = rhs.cString[i];
		}
	}
	assert(Invariant());
	return *this;
}
String & String::operator+=(const String & rhs)
{
	return *this;
}
String String::operator+()
{
	return String();
}
//Tvek på denna 
void String::reserve(size_t n)
{
	assert(Invariant());
	cString = new char[n];
	for (size_t i = 0; i < n; i++) {
		cString[i] = char();
	}
	length = n;
	assert(Invariant());
}

char & String::at(size_t i)
{
	try
	{
		if (i > holds)
			throw 1;
		else
			return cString[i];
	}
	catch (int x)
	{
		cout << "out_of_range, ERROR NUMBER: " + x << endl;
	}
	return cString[i];
}
void String::shrink_to_fit()
{
	assert(Invariant());
	char* temp = new char[holds + 1];
	for (size_t i = 0; i < holds; i++) {
		temp[i] = cString[i];
	}
	cString = temp;
	cString[holds] = 0;
	length = holds;
	delete[] temp;
	assert(Invariant());
}
void String::push_back(char c)
{
	assert(Invariant());
	if (holds == capacity() || capacity() == 0)
	{
		size_t n;
		if (capacity() == 0)
			n = 1;
		else
			n = 2 * capacity();

		char* temp = new char[n];
		for (size_t i = 0; i < holds; i++) {
			temp[i] = cString[i];
		}
		cString = temp;
		cString[holds] = 0;
		length = n;
	}
	cString[holds++] = c;
	cString[holds] = 0;
	assert(Invariant());
}
void String::resize(size_t n)
{
	assert(Invariant());
	char* temp = new char[n];
	for (size_t i = 0; i < n; i++) {
		temp[i] = cString[i];
		if (i > holds)
			temp[i] = char();
	}
	holds = n;
	length = n;
	cString = temp;
	assert(Invariant());
}
bool operator==(const String & lhs, const String & rhs)
{
	if (lhs.holds != rhs.holds)
		return false;
	else
	{
		for (size_t i = 0; i < lhs.size(); i++) {
			if (lhs.cString[i] != rhs.cString[i])
				return false;
		}
	}
	return true;
}
bool operator!=(const String & lhs, const String & rhs)
{
	if (lhs.size() != rhs.size())
		return true;
	else
	{
		for (size_t i = 0; i < lhs.size(); i++) {
			if (lhs.cString[i] != rhs.cString[i])
				return false;
		}
	}
	return true;
}

