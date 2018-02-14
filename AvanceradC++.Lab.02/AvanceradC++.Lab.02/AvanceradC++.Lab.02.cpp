// AvanceradC++.Lab.02.cpp : Defines the entry point for the console application.
//

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include "stdafx.h"
#include "VG.h"
#include "Rational.h"
#include "RelOps.h"
#include <cassert>
#include <crtdbg.h>
#include <assert.h>

//#include <iostream>
//using namespace std;

#include <limits>

#ifdef VG
//Kollar att int räknar med 64 bitar internt
bool TestAccuracy() {
	Rational<int> left(std::numeric_limits<int>::max(), 2), right(left), result;
	result = left + right;
	assert(result == Rational<int>(std::numeric_limits<int>::max(), 1));
	return true;
}


template<class Result, class L, class R>
bool CheckPlus(Result, L l, R r) {
	auto res = l + r;
	assert((std::is_same<Result, decltype(l + r)>::value));
	return std::is_same<Result, decltype(l + r)>::value;;
};
// Testar om Rational är komptaibelt med int, shar, long long
//  använder + för att prova detta.
bool TestCompatibility() {
	bool res = true;
	res &= CheckPlus(Rational<short>(), Rational<short>(), Rational<short>());
	res &= CheckPlus(Rational<int>(), Rational<short>(), Rational<int>());
	res &= CheckPlus(Rational<long long>(), Rational<long long>(), Rational<short>());
	res &= CheckPlus(Rational<long long>(), long long(), Rational<short>());
	res &= CheckPlus(Rational<long long>(), Rational<short>(), long long());
	res &= CheckPlus(Rational<short>(), Rational<short>(), Rational<long>());  //Rational<long> is more correct
	return res;
}

#endif VG

void TestFörGodkänt() {

	Rational<short> rs0, rs1(1), rs2(2, 1), rs3(3);
	Rational<int> ri0;
	Rational<long long> rll0, rll1(1), rll2(2, 1), rll3(3);

	//Konstrueras från ”Tal” dvs. Rtal rtal(tal);
	RLL   rllx(1);
	RLL   rlly(rs0);

	//Jämföras med == dvs. if (rtal == tal) …
	assert(rs1 == rs1);
	assert(rs2 == 2);
	assert(rs1 == rll1);
	assert(rs1 == Rational<short>(rs1.P, rs1.Q));
	assert(rs1 == Rational<short>(-rs1.P, -rs1.Q));
	/*assert(rs1 == Rational<short>(rs1.nom, rs1.denom));
	assert(rs1 == Rational<short>(-rs1.nom, -rs1.denom));*/

	//Tilldelas (=) från ”Tal” dvs. rtal=tal;
	rs3 = Rint(13, 3);
	assert(rs3 == Rshort(13, 3));
	rs3 = rll3 = -17;
	assert(rs3 == Rshort(-17));

	//+= med ”Tal” dvs. rtal += tal;
	assert((rs3 += 4) == Rshort(-13));

	//+  dvs. (rtal + tal)
	rs3 = Rshort(13, 3);
	assert(rs3 + rll2 == Rshort(19, 3));
	assert(rs3 + 2 == Rshort(19, 3));

	//unärt ”–” dvs. rtal1 = -rtal2;
	assert((rs0 = -rs1) == Rshort(-1));

	//båda ++ operatorerna, dvs. ++rtal; rtal++;
	rll3 = RLL(1, 6);
	assert(++rll3 == RLL(7, 6));
	assert(rll3++ == RLL(7, 6));
	assert(rll3 == RLL(13, 6));

	// explicit konvertering till Tal. (Kräver VS2012 och kompilator CTnom november 12.
	int i = static_cast<int>(rll3);
	assert(i == 2);

	// Overloading av << och >> (ut och in matning)
	std::cout << "Utmatning>" << rs3 << "< skriv in texten mellan > och < + retur\n";
	std::cin >> rs2;
	assert(rs3 == rs2);
}

#ifdef VG
void TestFörVälGodkänt() {

	assert(TestAccuracy());
	assert(TestCompatibility());

	Rshort rs(3, 2); Rint ri(2, 1); RLL rl;
	assert(!(1 == rs));
	assert(2 == ri);

}
9
#endif


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	TestFörGodkänt();
	return 0;
}

