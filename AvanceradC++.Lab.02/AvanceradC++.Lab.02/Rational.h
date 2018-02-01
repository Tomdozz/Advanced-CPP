#pragma once
#include<iostream>

template<typename Tint>
class Rational
{
public:
	Tint P, Q;
	friend std::ostream& operator<<(std::ostream & cout, Rational<Tint> R)
	{
		cout << R.P << "/" << R.Q;
	}
	Rational() : nom(0), denom(1) {};
	Rational(Tint P) : P(P), Q(1) {}
	Rational(Tint P, Tint Q) : P(P), Q(Q)
	{
		Reduce(P, Q);
	}
	Rational operator+(const Rational rhs)const :
	{

	}
	~Rational();
};

