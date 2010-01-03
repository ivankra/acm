// Simple rational arithmetic class.
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <sstream>
using namespace std;

template<typename T>
struct Rational {
	typedef Rational<T> R;
	T p, q;
	
	Rational(T p = 0, T q = 1) : p(p), q(q) { reduce(); }

	void reduce() {
		if (q < 0) { p = -p; q = -q; }
		T g = __gcd(p < 0 ? -p : p, q); p /= g; q /= g;
	}

	R operator +(const R &b) const { return R(p*b.q+q*b.p, q*b.q); }
	R operator -(const R &b) const { return R(p*b.q-q*b.p, q*b.q); }
	R operator *(const R &b) const { return R(p*b.p, q*b.q); }
	R operator /(const R &b) const { return R(p*b.q, q*b.p); }
	R operator -() const { return R(-p, q); }

#if 1
	bool operator <(const R &b) const { return p*b.q < q*b.p; }
	bool operator <=(const R &b) const { return p*b.q <= q*b.p; }
#else
	// ordered pair comparison
	bool operator <(const R &b) const { return p < b.p || (p == b.p && q < b.q); }
#endif
	bool operator ==(const R &b) const { return p == b.p && q == b.q; }
	bool operator !=(const R &b) const { return p != b.p || q != b.q; }

	string str() { ostringstream o; o << p << "/" << q; return o.str(); }
};

typedef Rational<long long> Frac;

int sign(const Frac &f) { return f.p==0 ? 0 : (f.p<0 ? -1 : 1); }
Frac abs(const Frac &f) { return Frac(f.p < 0 ? -f.p : f.p, f.q); }

long long floor(const Frac &f) { return f.p < 0 ? -((-f.p+f.q-1)/f.q) : (f.p/f.q); }
long long ceil(const Frac &f) { return f.p < 0 ? -((-f.p)/f.q) : ((f.p+f.q-1)/f.q); }

long long trunc(const Frac &f) { return f.p < 0 ? -((-f.p)/f.q) : (f.p/f.q); }
long long round(const Frac &f) {
	if (f.p >= 0) return (2*f.p+f.q)/(2*f.q);
	return -((-2*f.p+f.q) / (2*f.q));
}



// Tests
#if 1
int main() {
	typedef Frac F;

	assert(F(6,10).str() == "3/5");
	assert(F(-6,10).str() == "-3/5");
	assert(F(0,10).str() == "0/1");
	assert(F(-12345).str() == "-12345/1");
	assert(F(123,-456) == F(-123,456));
	assert(F(0,-456) == F(0));
	assert(F(0) == F(0));
	assert(F(1) == F(1));
	assert(F(-1) == -F(1));
	assert(-F(42) == F(-42));
	assert(-F(-42) == F(42));
	assert(F(0) != F(1));
	assert(F(-1) != F(1));
	assert(F(-12345) < F(12345));
	assert(!(F(123) <= F(-123)));

	assert(F(1,2) + F(1,2) == F(1));
	assert(F(10,20) + F(100000,400000) == F(300,400));
	assert(-(F(10,20) - F(100000,400000)) == F(0)+F(-10,40));
	assert(F(2,3) * F(3*7,2) == F(7));
	assert(F(2,3) * 11 * F(3,2) / 7 == F(110,70));

	assert(abs(F(42)) == F(42));
	assert(abs(F(-42)) == F(42));
	assert(abs(F(0)) == F(0));

	assert(sign(F(12345)) == 1);
	assert(sign(F(-12345)) == -1);
	assert(sign(F(0)) == 0);

	assert(floor(F(0,10)) == (0));
	assert(floor(F(1,10)) == (0));
	assert(floor(F(5,10)) == (0));
	assert(floor(F(9,10)) == (0));
	assert(floor(F(10,10)) == (1));
	assert(floor(F(10001,10000)) == (1));
	assert(floor(F(79999,10000)) == (7));
	assert(floor(F(80001,10000)) == (8));
	assert(floor(F(-1,10)) == -1);
	assert(floor(F(-5,10)) == -1);
	assert(floor(F(-9,10)) == -1);
	assert(floor(F(-10,10)) == -1);
	assert(floor(F(-10001,10000)) == -2);
	assert(floor(F(-79999,10000)) == -8);
	assert(floor(F(-80001,10000)) == -9);

	assert(ceil(F(0,10)) == (0));
	assert(ceil(F(1,10)) == (1));
	assert(ceil(F(5,10)) == (1));
	assert(ceil(F(9,10)) == (1));
	assert(ceil(F(10,10)) == (1));
	assert(ceil(F(10001,10000)) == (2));
	assert(ceil(F(79999,10000)) == (8));
	assert(ceil(F(80001,10000)) == (9));
	assert(ceil(F(-1,10)) == 0);
	assert(ceil(F(-5,10)) == 0);
	assert(ceil(F(-9,10)) == 0);
	assert(ceil(F(-10,10)) == -1);
	assert(ceil(F(-10001,10000)) == -1);
	assert(ceil(F(-79999,10000)) == -7);
	assert(ceil(F(-80001,10000)) == -8);

	assert(trunc(F(0,10)) == (0));
	assert(trunc(F(1,10)) == (0));
	assert(trunc(F(5,10)) == (0));
	assert(trunc(F(9,10)) == (0));
	assert(trunc(F(10,10)) == (1));
	assert(trunc(F(10001,10000)) == (1));
	assert(trunc(F(79999,10000)) == (7));
	assert(trunc(F(80001,10000)) == (8));
	assert(trunc(F(-1,10)) == 0);
	assert(trunc(F(-5,10)) == 0);
	assert(trunc(F(-9,10)) == 0);
	assert(trunc(F(-10,10)) == -1);
	assert(trunc(F(-10001,10000)) == -1);
	assert(trunc(F(-79999,10000)) == -7);
	assert(trunc(F(-80001,10000)) == -8);

	// round() rounds away from zero
	assert(round(F(0,10)) == (0));
	assert(round(F(1,10)) == (0));
	assert(round(F(5,10)) == (1));
	assert(round(F(9,10)) == (1));
	assert(round(F(10,10)) == (1));
	assert(round(F(10001,10000)) == (1));
	assert(round(F(79999,10000)) == (8));
	assert(round(F(80001,10000)) == (8));
	assert(round(F(-1,10)) == 0);
	assert(round(F(-5,10)) == -1);
	assert(round(F(-9,10)) == -1);
	assert(round(F(-10,10)) == -1);
	assert(round(F(-10001,10000)) == -1);
	assert(round(F(-79999,10000)) == -8);
	assert(round(F(-80001,10000)) == -8);
	printf("ok\n");
}
#endif
