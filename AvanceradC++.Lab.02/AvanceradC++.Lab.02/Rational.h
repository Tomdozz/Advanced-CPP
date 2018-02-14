#pragma once
#include <iostream>
#include "GCD.h"

template<typename Tint>
class Rational
{
public:
	Tint P, Q;
	friend std::ostream& operator<<(std::ostream & cout, Rational<Tint> R)
	{
		cout << R.P << "/" << R.Q;
		return cout;
	}

	friend std::istream& operator >> (std::istream & cin, Rational<Tint>& R)
	{
		cin >> R.P;
		cin >> R.Q;
		return cin;
	}

	//Rational() : nom(0), denom(1) {};
	Rational() : P(0), Q(1) {}
	Rational(Tint P) : P(P), Q(1) {}
	Rational(Tint P, Tint Q) : P(P), Q(Q)
	{
		Reduce(P, Q);
	}

	//Create a Rational number from a rational number
	template<typename Other>
	Rational(Rational<Other>& rhs) : P(rhs.P), Q(rhs.Q) {}

	template<typename Other>
	Rational operator-(const Rational<Other> rhs) const
	{
		Tint commonDenom = Q * rhs.Q;
		Tint num1 = P *rhs.P;
		Tint num2 = rhs.P * P;
		Tint diff = num1 + num2;
		Rational<Tint> returnTint;
		returnTint.P = diff;
		returnTint.Q = commonDenom;
		this = returnTint;

		return *this;
	}

	Rational operator=(const Rational rhs)
	{
		Q = rhs.Q;
		P = rhs.P;
		return *this;
	}

	template<typename Other>
	friend bool operator==(const Rational<Tint> lhs, const Rational<Other> rhs)
	{
		if (lhs.P / lhs.Q == rhs.P / rhs.Q)
		{
			return true;
		}
		else
			return false;
	}

	template<typename Other>
	Rational operator+=(const Rational<Other>& rhs)
	{
		int commonQ = Q*rhs.Q;
		int p1 = P*rhs.Q;
		int p2 = rhs.P *Q;
		int newP = p1 + p2;
		Reduce(newP, commonQ);

		P = newP;
		Q = commonQ;
		return *this;
	}

	Rational operator+=(const int i)
	{
		P += (Q*i);
		Reduce(P, Q);
		return *this;
	}

	Rational operator++()
	{
		return *this += 1;
	}

	Rational operator++(int)
	{
		Rational temp(*this);
		operator++();
		return temp;
	}


	template<typename Other>
	Rational operator+(const Rational<Other> rhs) const
	{
		Rational temp(*this);
		return temp += rhs;
	}

	Rational operator+(const int i) const
	{
		Rational temp(*this);
		return temp += i;
		//return *this;
	}

	operator int()
	{
		return (P / Q);
	}
	//~Rational();
};

