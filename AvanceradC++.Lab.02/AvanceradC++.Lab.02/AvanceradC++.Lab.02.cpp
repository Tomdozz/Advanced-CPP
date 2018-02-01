// AvanceradC++.Lab.02.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Rational.h"
#include <limits>
#include <cassert>
#include <iostream>
//using namespace std;
class RLL :public Rational<RLL> 
{
	
};
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
	assert(rs1 == Rational<short>(rs1.nom, rs1.denom));
	assert(rs1 == Rational<short>(-rs1.nom, -rs1.denom));

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

int main()
{
    return 0;
}

