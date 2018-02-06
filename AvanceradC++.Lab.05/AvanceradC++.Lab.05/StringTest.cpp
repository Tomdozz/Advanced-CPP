#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
#include <stdlib.h>
#include <crtdbg.h>
#include <cassert>
#include "stdafx.h"

#include "VG (1).h"

//#include "UnsignedTest.h"
#include "String.h"

//#include <string>

#include <iostream>
using std::cout;
using std::cin;

#include <cassert>

//#include <utility>
#include"StringTest.h"

//#include <iostream>
//#include <vector>

void PrintReallocationScheme() {
	typedef String Vector;
	size_t sz;

	Vector foo;
	sz = foo.capacity();
	std::cout << "mGrowing from default:\n";
	std::cout << "capacity is: " << sz << '\n';
	for (int i = 0; i < 100; ++i) {
		foo.push_back(i);
		if (sz != foo.capacity()) {
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}

	Vector bar;
	bar.reserve(100);   // this is the only difference with foo above
	sz = bar.capacity();
	std::cout << "reserve(100) no reallocations\n";
	std::cout << "capacity is: " << sz << '\n';
	for (int i = 0; i < 100; ++i) {
		bar.push_back(i);
		if (sz != bar.capacity()) {
			sz = bar.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
	std::cin.get();
}

void TestPushBackReallocation() {
	String str("hej");
	assert(str.size() <= str.capacity());

#ifdef VG
	//If VG we try to take 20 empty places: (size+1 < capacity)
	//we push_back one more until it is more then 20 places left (or sting to big)
	while (str.size() + 20 >= str.capacity() && str.size() < 1000)
		str.push_back('A' + rand() % 32);
	assert(str.size() < 1000);	//If this fail it prbably the case that capacity is increased with a constant.
#endif //VG

	auto internalBuf = str.data();
	auto cap = str.capacity();
	auto siz = str.size();
	int i;
	for (i = siz + 1; i <= cap; ++i) {
		str.push_back(char(i) + 'a');
		assert(internalBuf == str.data());
		assert(cap == str.capacity());
		assert(i == str.size());
	}
	str.push_back(char(i));
	assert(internalBuf != str.data());
	assert(cap < str.capacity());
	assert(i == str.size());

	assert(str.size() != str.capacity());
	internalBuf = str.data();
	cap = str.capacity();
	siz = str.size();
	str.shrink_to_fit();
	assert(internalBuf != str.data());
	assert(str.size() == str.capacity());
	assert(i == str.size());

	str = "hej";
	str.resize(10);
	assert(10 == str.size() && str[7] == char());
	cap = str.capacity() + 10;
	str.resize(cap);
	assert(str.size() == cap && str.capacity() >= cap);
}

void TestFörGodkäntString() {

	String str0;
	String str00("");
	assert(str0 == str00);
	str0 != str00;

	String s1("foo"); assert(s1 == "foo");
	String str(s1); assert(str == "foo");
	String s3("bar");  assert(s3 == "bar");


	delete new String("hej");


	assert((str = s3) == s3);
	assert((str = str) == s3);


	String str1("foo"), str2("bar"), str3("hej");
	str3 = str = str1;
	assert(str3 == str);
	assert(str1 == str);

	assert(String("huj"));
	assert(!String(""));

	str = "bar";
	str[-1]; str[1000];	//No error
	assert(str[1] == 'a');
	str[1] = 'y';
	assert(str[1] == 'y');

	const String sc(str);
	assert(sc[1] == 'y');
	assert(std::is_const<std::remove_reference< decltype(sc[1])>::type>::value);
	str = "bar";
	str.push_back('a');
	assert(str == "bara");
	str.push_back('\0');
	str.push_back('x');
	assert(str.size() == 6 && str[4] == '\0' && str[5] == 'x');
	TestPushBackReallocation();
	PrintReallocationScheme();

	cout << String("hej\n");
	cout << "Om det står hej på föregående rad så är TestFörGodkänt klar\n";

}

#ifdef VG

void TestFörVälGodkäntString() {
	String str("bar");

	//-	at(int i) som indexerar med range check
	try {
		str.at(-1);
		assert(false);
	}
	catch (std::out_of_range&) {};
	try {
		str.at(3);
		assert(false);
	}
	catch (std::out_of_range&) {};

	//- at indexerar

	//-	at(int i) 
	str = "bar";
	assert(str.at(1) == 'a');
	str.at(1) = 'y';
	assert(str.at(1) == 'y');

	const String strC(str);
	assert(strC.at(1) == 'y');
	assert(std::is_const<std::remove_reference< decltype(strC.at(1))>::type>::value); //Kolla att det blir en const resultat av indexering

																					  // ConvertToChars
	const char* temp = strC.data();
	assert(strC.size() == 3);
	assert(std::memcmp(temp, strC.data(), strC.size()) == 0);
	assert(temp[strC.size()] == '\0');

	//	reserve()
	auto internalBuf = str.data();
	auto cap = str.capacity();
	auto siz = str.size();

	str.reserve(cap);
	assert(internalBuf == str.data());
	assert(cap == str.capacity());
	assert(siz == str.size());

	str.reserve(cap + 1);
	assert(internalBuf != str.data());
	assert(cap + 1 == str.capacity());
	assert(siz == str.size());

	/////////////////
	//-	operator+=(Sträng sträng) som tolkas som konkatenering.
	//foo, bar, hej
	String str1("foo"), str2("bar"), str3("hej");
	((str = "xyz") += str1) += (str3 += str1);
	assert(str3 == "hejfoo" && str == "xyzfoohejfoo" && str1 == "foo");

	//+= som får plats;
	str = "bar";
	str.reserve(10);
	str += "foo";
	assert(str == "barfoo");

	//+= som inte får plats;
	str.reserve(10);
	str = "";
	int i;
	for (i = 0; str.size() < str.capacity(); ++i)
		str.push_back('0' + i);
	str1 = "bar";
	str += str1;
	for (int k = 0; k < i; ++k)
		assert(str[k] == '0' + k);
	assert(str[i] == 'b');
	//+= Själv assignment	//Borde testa med att capacity tar slut!
	str = "foo";
	str += str;
	assert(str == "foofoo");

	//-	operator+
	str = "bar";
	assert(str + String("foo") == "barfoo");

	//move
	const char* strdata = str.data();
	String mStr(std::move(str));
	assert(strdata == mStr.data());
	assert(nullptr == str.data());

	str = std::move(mStr);
	assert(strdata == str.data());
	assert(nullptr == mStr.data());

	cout << "\nTestFörVälGodkänt klar\n";
}

#endif //VG

