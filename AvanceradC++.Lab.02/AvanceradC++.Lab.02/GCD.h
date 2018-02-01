#include <cassert>

template<typename Tint>
Tint GCD(Tint A, Tint B) {
	A = abs(A);
	B = abs(B);
	if (A < B)
		return GCD(B, A);
	while (B != 0) {
		Tint temp = A%B;
		A = B;
		B = temp;
	}
	return A;
}

template<typename Tint>
void Reduce(Tint& A, Tint& B) {
	Tint gcd = GCD(A, B);
	if (B < 0) gcd = -gcd;
	A /= gcd;
	B /= gcd;
}


template<typename Tint>
void TestGCD() {
	assert(GCD(30, 42) == 6);
	assert(GCD(30, -42) == 6);
	assert(GCD(-30, 42) == 6);
	assert(GCD(-30, -42) == 6);
	assert(GCD(30, 42) == 6);
}

