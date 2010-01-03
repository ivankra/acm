/* Number theoretic algorithms */
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;

typedef long long i64;
typedef unsigned long long u64;

/* Integer square root.  isqrt(n) = floor(sqrt(n)) */

unsigned isqrt(unsigned n) {
	unsigned x = 0;
	for (int i = 15; i >= 0; i--)
		if (((x|(1<<i)) * (x|(1<<i))) <= n) x |= 1 << i;
	return x;
}

u64 isqrt(u64 n) {
	u64 x = 0;
	for (int i = 31; i >= 0; i--)
		if (((x|(1ULL<<i)) * (x|(1ULL<<i))) <= n) x |= 1ULL << i;
	return x;
}

/* Binary GCD algorithm. */
template<typename T> T bingcd(T a, T b) {
	if (a < 0) a = -a;
	if (b < 0) b = -b;

	int k = 0;
	while (((a | b) & 1) == 0) { a >>= 1; b >>= 1; k++; }

	for (;;) {
		if (a == 0) return b << k;
		if (b == 0) return a << k;
		while ((a & 1) == 0) a >>= 1;
		while ((b & 1) == 0) b >>= 1;
		if (a > b) a -= b; else b -= a;
	}
}

/* Use <algorithm>'s __gcd(a,b) for usual euclid's gcd. [gcc only] */

/* Extended GCD.  Finds x,y such that ax + by = g = gcd(a, b). */
template<typename T> void gcdext(T &g, T &x, T &y, T a, T b) {
	if (b == 0) {
		g = a; x = 1; y = 0;
	} else {
		gcdext(g, y, x, b, a % b);
		y = y - (a / b) * x;
	}
}

/* Finds g = gcd(a,b) and x,y such that ax + by = g (mod m). */
template<typename T> void gcdextm(T &g, T &x, T &y, T a, T b, T m) {
	if (b == 0) {
		g = a; x = 1; y = 0;
	} else {
		gcdextm(g, y, x, b, a % b, m);
		y -= ((a / b) * x) % m;
		while (y < 0) y += m;
	}
}

/* Modular inverse.
   Returns x such that ax = 1 (mod m), or -1 if no such x exists. */
template<typename T> T modinv(T a, T m) {
	T g, x, y;
	gcdextm(g, x, y, a, m, m);
	if (g < 0) g = -g;
	return (g == 1) ? (x % m) : -1;
}

/* Modular inverse.  Computes x such that ax = 1 (mod m).  Returns false if
   such x does not exist. */
template<typename T> bool modinv(T &x, T a, T m) {
	T g, y;
	gcdextm(g, x, y, a, m, m);
	if (g < 0) g = -g;
	if (g != 1) return false;
	x = x % m;
	return true;
}

/*
 *  Linear diophantine equation: ax+by=c.
 *  Let d=gcd(a,b).  The equation has integer solutions iff d|c.
 *  
 *  ax + by = d
 *  Directly solvable by the extended GCD algorithm.
 *
 *  If (x0, y0) is a solution of ax+by=d, then (x0*c/d, y0*c/d) is a solution
 *  of ax+by=c.
 *
 *  If (x0, y0) is a solution of ax+by=c, then all solutions (x,y) are given by
 *    x = x0 + b/d t
 *    y = y0 - a/d t
 *  where t is an arbitrary integer.
 */

/*
 *  Solves linear diophantine equation ax+by=c.
 *  Returns false if there are no solutions.  Otherwise returns true,
 *  sets (x,y) to one of solutions, all solutions are: (x+dx*t, y+dy*t), t in Z.
 */
template<typename T> bool ldioph(T &x, T &y, T &dx, T &dy, T a, T b, T c) {
	T d; gcdext(d, x, y, a, b);
	if (c % d != 0) {
		return false;
	} else {
		x *= c / d; y *= c / d; dx = b / d; dy = -a / d;
		return true;
	}
}


/*
 *  Modular linear equation: ax = b (mod m)
 *
 *  The equation has no solutions iff b != 0 (mod gcd(a,m)).
 */

/* msolve asserts: a>=0, b>=0, m>=1 */

/* Solves linear modular equation: ax = b (mod m).
   Computes smallest non-negative solution x.
   All solutions are of form: x + dx t, t in Z. */
template<typename T> bool msolve(T &x, T &dx, T a, T b, T m) {
	T g;

	gcdext(g, x, dx, a, m);
	if (b % g != 0) return false;

	x *= b / g; dx = m / g;
	if (x < 0) { x = dx - ((-x) % dx); if (x == dx) x = 0; } else x %= dx;
	return true;
}

/* Solves linear modular equation: ax = b (mod m)
   Returns a sorted list of all solutions x, such that 0 <= x < m.
   Note: if equation has solutions, msolve() will return gcd(a, m) solutions. */
template<typename T> vector<T> msolve(T a, T b, T m) {
	T g, x, y;
	vector<T> r;

	gcdext(g, x, y, a, m);
	if (b % g != 0) return r;

	x *= b / g; y = m / g;
	if (x < 0) { x = y - ((-x) % y); if (x == y) x = 0; } else x %= y;
	for (int t = (int)g; t-- > 0; x += y) r.push_back(x);
	return r;
}


/*
 *  Chinese Remainder Theorem.
 *  (Generalized version, relative primality of moduli is not assumed.)
 *
 *  System of equations to be solved:
 *  x = a (mod m),  x = b (mod n)          (1)
 *
 *  Let g = gcd(m, n)
 *
 *  System (1) is equivalent to:
 *    x = a + m t           (2a)
 *    x = b + n s           (2b)
 *    for some t, s in Z
 *
 *  Combining (2a) and (2b), get:
 *    b-a = g(m/g t - n/g s).
 *  Hence, a necessary condition of existence of integer solutions is:
 *    a = b (mod g), i.e. g|(b-a)
 *
 *  m t + n (-s) = b-a     -- linear diophantine equation.
 *
 *  m T + n S = g          -- find one solution (T,S) with extended gcd.
 *  m [T(b-a)/g] + n [S(b-a)/g] = b-a
 *
 *  All solutions (t,s) for system (2a),(2b) are given by:
 *    t = T(b-a)/g + n/g z
 *    s = S(a-b)/g + m/g z
 *    z in Z
 *
 *  Let L = lcm(m, n) = mn/g
 *  x = a + T(b-a) m/g (mod L)
 *  x = b + S(a-b) n/g (mod L)
 *  (the two are equivalent)
 */

/* Solves system: x = a (mod m), x = b (mod n). */
template<typename T> bool crt(T &x, T &M, T a, T m, T b, T n) {
	T g, t, s;
	gcdext(g, t, s, m, n);
	if (((a - b) % g) != 0) return false;
	M = m / g * n;
	x = a + m / g * t * (b - a);
	if (x < 0) { x = M - ((-x) % M); if (x == M) x = 0; } else x %= M;
	return true;
}


/* Lightweight version of modinv */

int int_modinv(int a, int m)
{
	int b = m, x = 1, y = 0, t;
	for (a %= m; a != 0;) {
		t = y-(b/a)*x; y = x; x = t;
		t = b%a; b = a; a = t;
	}
	if (b != 1) return -1;
	return (y < 0) ? (m - (-y) % m) : (y % m);
}


/*****************************************************************************/
/** TEST SUITE **/
int main()
{
	printf("bingcd "); fflush(stdout); {
		for (int a = -100; a < 100; a++) {
			for (int b = -100; b < 100; b++) {
				if (a == 0 && b == 0) continue;
				assert(bingcd(a,b) == __gcd(abs(a),abs(b)));
			}
		}
	} printf("ok\n");

	printf("gcdext "); fflush(stdout); {
		for (int a = -100; a < 100; a++) {
			for (int b = -100; b < 100; b++) {
				if (a == 0 && b == 0) continue;
				int g, x, y;
				gcdext(g, x, y, a, b);
				assert(abs(g) == __gcd(abs(a),abs(b)));
				assert(a*x+b*y==g);
			}
		}
	} printf("ok\n");

	printf("modinv "); fflush(stdout); {
		for (int a = 1; a < 31337; a++) {
			int x = modinv(a, 31337);
			assert(0 <= x && x < 31337 && ((a * x) % 31337) == 1);
		}
		for (int a = 0; a < 50000; a++) {
			int m = 7854, x = modinv(a, m);
			if (x == -1)
				assert(__gcd(a % m, m) > 1);
			else
				assert(0 <= x && x < m && ((a * x) % m) == 1);
		}
		assert(modinv(2, 10) == -1);
		assert(modinv(5, 10) == -1);
		assert(modinv(3, 10) == 7);
	} printf("ok\n");

	printf("modinv[2] "); fflush(stdout); {
		int x;
		for (int a = 1; a < 31337; a++) {
			assert(modinv(x, a, 31337));
			assert(0 <= x && x < 31337 && ((a * x) % 31337) == 1);
		}
		for (int a = 0; a < 50000; a++) {
			int m = 7854;
			if (!modinv(x, a, m))
				assert(__gcd(a % m, m) > 1);
			else
				assert(0 <= x && x < m && ((a * x) % m) == 1);
		}
		assert(!modinv(x, 2, 10));
		assert(!modinv(x, 5, 10));
		assert(modinv(x, 3, 10) && x == 7);
	} printf("ok\n");

	printf("int_modinv "); fflush(stdout); {
		for (int m = 2; m <= 300; m++) {
			for (int a = 0; a <= 300; a++) {
				int i = int_modinv(a, m);
				if (__gcd(a, m) != 1) {
					assert(i == -1);
				} else {
					assert(i >= 0 && i < m && (a*i)%m == 1%m);
				}
			}
		}
	} printf("ok\n");

	printf("ldioph "); fflush(stdout); {
		int x0, y0, dx, dy, g=-2*3*7*11, a=-7*g, b=27*g, c=256*g;
		assert(ldioph(x0, y0, dx, dy, a, b, c));
		for (int t = -100; t <= 100; t++) {
			int x = x0 + dx * t;
			int y = y0 + dy * t;
			assert(a*x + b*y == c);
		}
	} printf("ok\n");

	printf("crt "); fflush(stdout); {
		i64 x, m;
		for(i64 M=1;M<100;M++) for(i64 A=-100;A<=100;A++) {
			assert(crt<i64>(x,m, A,M, A,M) && (A-x)%M == 0 && m == M);
			assert(crt<i64>(x,m, M+A,M, A,M) && (A-x)%M == 0 && m == M);
			assert(crt<i64>(x,m, A,M, A+M,M) && (A-x)%M == 0 && m == M);
			assert(crt<i64>(x,m, 0,1, A,M) && (A-x)%M == 0 && m == M);
			assert(crt<i64>(x,m, A,M, 0,1) && (A-x)%M == 0 && m == M);
		}
		assert(crt<i64>(x,m, 2,3, 3,5) && x == 8 && m == 15);
		assert(crt<i64>(x,m, 8,15, 2,7) && x == 23 && m == 105);
		assert(crt<i64>(x,m, 0,1, 1,1) && x == 0 && m == 1);
		assert(crt<i64>(x,m, 0,1, 0,2) && x == 0 && m == 2);
		assert(crt<i64>(x,m, 0,2, 0,2) && x == 0 && m == 2);
		assert(!crt<i64>(x,m, 0,2, 1,2));
		assert(!crt<i64>(x,m, 0,2, 3,2));
		assert(crt<i64>(x,m, 1,2, 3,2) && x == 1 && m == 2);
		assert(crt<i64>(x,m, 2,2, 8,2) && x == 0 && m == 2);
		for (i64 M=1;M<15;M++) for(i64 N=1;N<15;N++) {
			for (i64 A=-15;A<15;A++) for(i64 B=-15;B<15;B++) {
				if (!crt<i64>(x,m, A,M, B,N)) {
					assert(((A-B) % __gcd(M,N)) != 0);
					continue;
				}
				assert(((A-B) % __gcd(M,N)) == 0);
				assert(m == M/__gcd(M,N)*N);
				assert((x-A)%M == 0 && (x-B)%N==0);
				assert((x-124*m-A)%M==0 && (x+333*m-B)%N==0);
			}
		}
	} printf("ok\n");

	printf("isqrt<unsigned> "); fflush(stdout); {
		assert(isqrt((unsigned)0) == 0);
		assert(isqrt((unsigned)1) == 1);
		assert(isqrt((unsigned)2) == 1);
		assert(isqrt((unsigned)3) == 1);
		for (unsigned x = 2; x <= 65535; x++) {
			unsigned s = x*x;
			assert(isqrt(s)==x);
			assert(isqrt(s-1) == x-1);
			assert(isqrt(s+1)==x);
		}
	} printf("ok\n");

	printf("isqrt<u64> "); fflush(stdout); {
		assert(isqrt((u64)0) == 0);
		assert(isqrt((u64)1) == 1);
		assert(isqrt((u64)2) == 1);
		assert(isqrt((u64)3) == 1);
		for (u64 x = 2; x < 100000; x++) {
			u64 s = x*x;
			assert(isqrt(s)==x);
			assert(isqrt(s-1) == x-1);
			assert(isqrt(s+1)==x);
		}
		for (u64 x = (1ULL<<32)-10000; x < (1ULL << 32); x++) {
			u64 s = x*x;
			assert(isqrt(s)==x);
			assert(isqrt(s-1) == x-1);
			assert(isqrt(s+1)==x);
		}
	} printf("ok\n");

	printf("msolve "); fflush(stdout); {
		for(int m=1;m<=50;m++) for(int a=0;a<=50;a++) for(int b=0;b<=50;b++) {
			int x, dx, g = __gcd(abs(a), abs(m));
			if (!msolve(x, dx, a, b, m)) {
				assert((b % g) != 0);
			} else {
				assert(0 <= x && x < m && 1 <= dx && x < dx);
				assert(g > 0 && dx == m/g);
				for (int i = 0; i < g; i++, x += dx)
					assert((a * x - b) % m == 0);
			}
                }
	} printf("ok\n");

	printf("msolve[vector] "); fflush(stdout); {
		for(int m=1;m<=30;m++) for(int a=0;a<=30;a++) for(int b=0;b<=30;b++) {
			vector<int> s = msolve(a, b, m);
			int g = __gcd(abs(a), abs(m));
			if (s.empty()) { assert((b % g) != 0); continue; }
			assert((int)s.size() == g);
			for (int i = 0; i < g; i++) {
				if (i > 0) assert(s[i-1] < s[i]);
				assert(0 <= s[i] && s[i] < m);
				assert((a * s[i] - b) % m == 0);
			}
                }
	} printf("ok\n");

	return 0;
}
