// AvanceradC++.Lab.05.cpp : Defines the entry point for the console application.
//
//kompilera och se glad ut-Olle 18

#include "stdafx.h"
#include "String.h"
#include <cassert>
#include <iostream>
#include <utility>
#include "StringTest.h"
#include "StringIttTest.h"
#include <vector>

using namespace std;

#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
#include "StringItt.h"

void Testing();
int main()
{
	std::locale::global(std::locale("swedish"));
	TestFörGodkäntString();
	TestFörGodkäntItt();
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//Testing();
	return 0;
}
void Testing()
{
	String str("hejsan");
	cout << str.size();
	assert(str.size() <= str.capacity());
}
