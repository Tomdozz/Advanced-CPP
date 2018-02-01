#include "stdafx.h"
#include "VG (1).h"

#include "String.h"
#include "StringItt.h"

//#include "ForwardSort.h"
//#include "HjälpProgram.h"
//#include <forward_list>
//using std::forward_list;

#include <iostream>
using std::cout;
using std::endl;

//#include <vector>
//using std::vector;

#include <algorithm>

//#ifdef ITT
//#ifdef workingProgress


//void TestIttInAlg() {
//
//    static const int N = 26;
//    String v;
//    v.reserve(N);
//    for (int i = 0; i < N; ++i) {
//        v.push_back('a' + i);
//    }
//    v.begin();
//    auto b = std::begin(v);
//    auto e = std::end(v);
//
//    std::random_shuffle(b, e);
//
//    cout << v << endl;
//    std::stable_sort(b, e);
//
//    cout << v << endl;
//
//}
//
//void TestRevIttInAlg() {
//
//    static const int N = 26;
//    String v;
//    v.reserve(N);
//    for (int i = 0; i < N; ++i) {
//        v.push_back('a' + i);
//    }
//    auto b = std::rbegin(v);
//    auto e = std::rend(v);
//
//    std::random_shuffle(b, e);
//
//    cout << v << endl;
//    std::stable_sort(b, e);
//
//    cout << v << endl;
//
//}

/*	*it, ++it, it++, (it+i), it[i], == och !=	*/
void TestIttPart() {
	String s1("foobar");
	for (auto i = s1.begin(); i != s1.end(); i++)
		cout << *i;
	cout << endl;
	//s1 = "raboof";
	auto it = s1.begin();
	assert(*it == 'f');
	assert(*(it++) == 'f' && *it == 'o');
	++it;
	assert(*++it == 'b');
	assert(*(it + 1) == 'a');
	assert(it[2] == 'r');
}

void TestIttPartR() {
    String s1("foobar");
    for (auto i = s1.rbegin(); i != s1.rend(); i++)
        cout << *i;
    cout << endl;
    s1 = "raboof";
    auto it = s1.rbegin();
    assert(*it == 'f');

    assert(*(it++) == 'f' && *it == 'o');
    ++it;
    assert(*++it == 'b');
    assert(*(it + 1) == 'a');
    assert(it[2] == 'r');
}
//#endif // workingProgress

#ifdef VG
void TestIttPartC() {
	String s1("foobar");
	for (auto i = s1.cbegin(); i != s1.cend(); i++)
		cout << *i;
	cout << endl;
	//    s1 = "raboof";
	auto it = s1.cbegin();
	assert(*it == 'f');
	assert(*(it++) == 'f' && *it == 'o');
	++it;
	assert(*++it == 'b');
	assert(*(it + 1) == 'a');
	assert(it[2] == 'r');
}

void TestIttPartCR() {
	String s1("foobar");
	for (auto i = s1.crbegin(); i != s1.crend(); ++i)
		cout << *i;
	cout << endl;
	s1 = "raboof";
	auto it = s1.crbegin();
	assert(*it == 'f');
	assert(*(it++) == 'f' && *it == 'o');
	++it;
	assert(*++it == 'b');
	assert(*(it + 1) == 'a');
	assert(it[2] == 'r');
}
#endif VG

void TestFörGodkäntItt() {

	//-	typdefs för iterator, const_iterator,  reverse_iterator och const_revers_iterator
	String::iterator Str;
	String::reverse_iterator rStr;

	//-	funktionerna begin, end, cbegin, cend, rbegin, rend, crbegin och crend.


	TestIttPart();
	TestIttPartR();
#ifdef VG
	String::const_iterator cStr;
	String::const_reverse_iterator crStr;
	TestIttPartC();
	TestIttPartCR();
#endif VG

	//Iteratorerna ska kunna göra:
	//-	*it, ++it, it++, (it+i), it[i], == och !=



	//-	default constructor, copy constructor och tilldelning (=) 
	String s("foobar");
	Str = s.begin();
	rStr = s.rbegin();

#ifdef VG
	cStr = s.cbegin();
	crStr = s.crbegin();
#endif VG

	*Str = 'a';
	//	*(cStr+1)='b';	//Sak ge kompileringsfel!
	*(rStr + 2) = 'c';
	//	*(crStr+3)='d';	//Sak ge kompileringsfel!
	assert(s == "aoocar");

	cout << "\nTestFörGodkänt Itt klar\n";
#ifdef VG
	cout << "\nTestFörVälGodkänt Itt klar\n";
#endif VG

}
//#endif Itt

