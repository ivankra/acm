#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;

// Version 20070111.2
class BigInt {
	int size;
	unsigned *data;
	int alloc;
	unsigned _data[5];

public:
	// Memory management
	void reserve(int n) {
		if (data == NULL) {
			data = _data;
			alloc = sizeof(_data)/sizeof(_data[0]);
		}

		if (alloc < n) {
			while (alloc < n) alloc <<= 1;
			if (data == _data) {
				data = (unsigned *)malloc(alloc * sizeof(unsigned));
				assert(data != NULL);
				memcpy(data, _data, sizeof(_data));
			} else {
				data = (unsigned *)realloc(data, alloc * sizeof(unsigned));
				assert(data != NULL);
			}
		}
	}

	~BigInt() {
		if (data != _data) free(data);
	}

	void swap(BigInt &y) {
		if (data != _data && y.data != y._data) {
			std::swap(size, y.size); std::swap(alloc, y.alloc);
			std::swap(data, y.data);
		} else {
			BigInt t(*this); assign(y); y.assign(t);
		}
	}
private:
	typedef unsigned long long uint64;
	static inline int sgn(int n) { return n == 0 ? 0 : (n < 0 ? -1 : 1); }

	// Removes leading zeroes
	void normalize() {
		int n = abs(size);
		while (n > 0 && data[n-1] == 0) n--;
		size = (size < 0 ? -n : n);
	}

	static int absCmp(const BigInt &x, const BigInt &y) {
		int xn = abs(x.size), yn = abs(y.size);
		if (xn != yn) return sgn(xn - yn);
		for (int i = xn-1; i >= 0; i--)
			if (x.data[i] != y.data[i]) return x.data[i] > y.data[i] ? +1 : -1;
		return 0;
	}

	// z = abs(x) + abs(y);
	static void absAdd(BigInt &z, const BigInt &x, const BigInt &y) {
		int xn = abs(x.size), yn = abs(y.size);
		if (xn < yn) { absAdd(z, y, x); return; }

		int zn = max(xn, yn);
		z.reserve(zn + 1);

		uint64 c = 0;
		for (int i = 0; i < yn; i++, c >>= 32)
			z.data[i] = (unsigned)((c += x.data[i] + (uint64)y.data[i]) & 0xFFFFFFFFU);

		if (&z == &x) {
			for (int i = yn; c != 0 && i < xn; i++, c >>= 32)
				z.data[i] = (unsigned)((c += x.data[i]) & 0xFFFFFFFFU);
		} else {
			for (int i = yn; i < xn; i++, c >>= 32)
				z.data[i] = (unsigned)((c += x.data[i]) & 0xFFFFFFFFU);
		}
		if (c != 0) z.data[zn++] = (unsigned)c;

		z.size = zn;
	}

	// z = abs(x) + abs(y)
	static void absAdd1(BigInt &z, const BigInt &x, unsigned y) {
		int n = abs(x.size);
		z.reserve(n+1);

		uint64 c = y;
		if (&z == &x) {
			for (int i = 0; c != 0 && i < n; i++, c >>= 32)
				z.data[i] = (unsigned)((c += x.data[i]) & 0xFFFFFFFFU);
		} else {
			for (int i = 0; i < n; i++, c >>= 32)
				z.data[i] = (unsigned)((c += x.data[i]) & 0xFFFFFFFFU);
		}
		if (c != 0) z.data[n++] = (unsigned)c;
		z.size = n;
	}

	// z = abs(x) - abs(y)
	static void absSub(BigInt &z, const BigInt &x, const BigInt &y) {
		int t = absCmp(x, y);
		if (t <= 0) {
			if (t == 0) z.size = 0; else absSub(z, y, x);
			z.size = -z.size;
			return;
		}

		int xn = abs(x.size), yn = abs(y.size);
		z.reserve(max(xn, yn));

		uint64 c = 1;
		for (int i = 0; i < yn; i++, c >>= 32) {
			c += (uint64)x.data[i] + ((uint64)y.data[i] ^ 0xFFFFFFFFULL);
			z.data[i] = (unsigned)(c & 0xFFFFFFFFU);
		}

		if (&z == &x) {
			for (int i = yn; c != 1 && i < xn; i++, c >>= 32)
				z.data[i] = (unsigned)((c += (uint64)x.data[i] + 0xFFFFFFFFULL) & 0xFFFFFFFFU);
		} else {
			for (int i = yn; i < xn; i++, c >>= 32)
				z.data[i] = (unsigned)((c += (uint64)x.data[i] + 0xFFFFFFFFULL) & 0xFFFFFFFFU);
		}
		assert(c == 1);

		z.size = xn;
		while (z.size > 0 && z.data[z.size-1] == 0) z.size--;
		assert(z.size > 0);
	}

	// z = abs(x) - abs(y)
	static void absSub1(BigInt &z, const BigInt &x, unsigned y) {
		if (y == 0) { z.assign(x); z.size = abs(z.size); return; }
		if (x.size == 0) { z.size = -1; z.data[0] = y; return; }

		int xn = abs(x.size);
		if (xn == 1) {
			if (x.data[0] > y) { z.size = 1; z.data[0] = x.data[0] - y; }
			else if (x.data[0] == y) { z.size = 0; }
			else { z.size = -1; z.data[0] = y - x.data[0]; }
			return;
		}
		z.reserve(xn);

		uint64 c = 1 + (uint64)x.data[0] + (y ^ 0xFFFFFFFFULL);
		z.data[0] = (unsigned)c;
		c >>= 32;

		if (&z == &x) {
			for (int i = 1; c != 1 && i < xn; i++, c >>= 32)
				z.data[i] = (unsigned)(c += (uint64)x.data[i] + 0xFFFFFFFFULL);
		} else {
			for (int i = 1; i < xn; i++, c >>= 32)
				z.data[i] = (unsigned)(c += (uint64)x.data[i] + 0xFFFFFFFFULL);
		}

		z.size = xn;
		while (z.size > 0 && z.data[z.size-1] == 0) z.size--;
	}

	// z = abs(x) * m + a
	static void absMulAdd1(BigInt &z, const BigInt &x, unsigned m, unsigned a) {
		int n = abs(x.size);
		z.reserve(n+2);

		uint64 c = a;
		for (int i = 0; i < n; i++, c >>= 32) {
			c = (c + (uint64)x.data[i] * (unsigned)m);
			z.data[i] = (unsigned)(c & 0xFFFFFFFFU);
		}
		while (c != 0) { z.data[n++] = (unsigned)c; c >>= 32; }

		z.size = n;
	}

	// z = x + sign*y.  Asserts: abs(sign) = 1
	static void add(BigInt &z, const BigInt &x, int sign, const BigInt &y) {
		int xs = sgn(x.size), ys = sign * sgn(y.size);
		if (xs == 0) { z.assign(y); z.size *= sign; }
		else if (ys == 0) z.assign(x);
		else if (xs == ys) { absAdd(z, x, y); z.size *= xs; }
		else if (ys < 0) absSub(z, x, y);
		else { absSub(z, x, y); z.size = -z.size; }
	}

	static void add1s(BigInt &z, const BigInt &x, int y) {
		int xs = (x.size >= 0 ? +1 : -1), ys = (y >= 0 ? +1 : -1);
		if (xs == ys) { absAdd1(z, x, abs(y)); z.size *= xs; }
		else if (ys < 0) { absSub1(z, x, -y); }
		else { absSub1(z, x, y); z.size = -z.size; }
	}

	static void mul1s(BigInt &z, const BigInt &x, int y) {
		if (y < 0) { mul1s(z, x, -y); z.size = -z.size; return; }
		if (y == 0) { z.size = 0; return; }
		if (y == 1) { z.assign(x); return; }

		int n = abs(x.size);
		z.reserve(n+1);

		uint64 c = 0;
		for (int i = 0; i < n; i++, c >>= 32) {
			c = (c + (uint64)x.data[i] * (unsigned)y);
			z.data[i] = (unsigned)(c & 0xFFFFFFFFU);
		}
		if (c != 0) z.data[n++] = (unsigned)c;

		z.size = (x.size < 0 ? -n : n);
	}

	static void mulQuadratic(BigInt &z, const BigInt &x, const BigInt &y) {
		if (&z == &x || &z == &y) {
			BigInt t;
			mulQuadratic(t, x, y);
			z = t;
			return;
		}

		int xn = abs(x.size), yn = abs(y.size), zn = xn + yn + 1;
		z.reserve(zn);
		for (int i = 0; i < zn; i++) z.data[i] = 0;

		for (int i = 0; i < xn; i++) {
			uint64 c = 0;
			int k = i;
			for (int j = 0; j < yn; j++, k++, c >>= 32) {
				c += z.data[k] + x.data[i] * (uint64)y.data[j];
				z.data[k] = (unsigned)(c & 0xFFFFFFFFU);
			}
			for (; c != 0; k++, c >>= 32)
				z.data[k] = (unsigned)((c += z.data[k]) & 0xFFFFFFFFU);
		}

		z.size = zn * sgn(x.size) * sgn(y.size);
		z.normalize();
	}

	static void mulKaratsuba(BigInt &z, const BigInt &x, const BigInt &y) {
		int xn = abs(x.size), yn = abs(y.size), zs = sgn(x.size) * sgn(y.size);
		int w = max(xn, yn) >> 1;
		BigInt A(x.data+w, max(0, xn-w)), B(x.data, min(xn, w));
		BigInt C(y.data+w, max(0, yn-w)), D(y.data, min(yn, w));
		BigInt R, T;
		absAdd(z, A, B);
		absAdd(T, C, D);
		mul(R, z, T);
		mul(z, A, C);
		mul(T, B, D);
		R -= z; R -= T; R <<= w*32;
		z <<= w*64; z += R; z += T; z.size *= zs;
	}

	BigInt(unsigned a[], int n) {
		if (n < 0) n = 0;
		while (n > 0 && a[n-1] == 0) n--;
		data = NULL;
		reserve(n);
		size = n;
		memcpy(data, a, n * sizeof(unsigned));
	}

	// q = abs(x) div abs(y);  Returns abs(x) mod abs(y)
	static unsigned absDiv1(BigInt &q, const BigInt &x, unsigned y) {
		assert(y != 0);

		int n = abs(x.size);
		q.reserve(n);

		uint64 c = 0;
		for (int i = n-1; i >= 0; i--) {
			c = (c << 32) | (uint64)x.data[i];
			q.data[i] = (unsigned)(c / y);
			c %= y;
		}
		q.size = n;
		q.normalize();
		return (unsigned)c;
	}

	// u = abs(u) mod abs(v), q = abs(u) div abs(v)
	static void absDiv(BigInt *q, BigInt &u, BigInt v) {
		if (q != NULL && q == &u) {
			BigInt t;
			absDiv(&t, u, v);
			*q = t;
			return;
		}

		u.size = abs(u.size);
		v.size = abs(v.size);
		assert(v.size > 0);

		if (u.size < v.size) { if (q) *q = 0; return; }
		if (v.size == 1) {
			unsigned t = absDiv1(q==NULL ? u : *q, u, v.data[0]);
			u.data[0] = t;
			u.size = (t == 0 ? 0 : 1);
			return;
		}

		int n = v.size, d = 0;
		while (((v.data[n-1] << d) & 0x80000000U) == 0) d++;
		u <<= d;
		v <<= d;

		unsigned vh = v.data[n-1], vh2 = v.data[n-2];
		uint64 c, g;

		u.reserve(u.size+1); u.data[u.size] = 0;
		v.reserve(v.size+1); v.data[v.size] = 0;

		int qp = u.size - v.size + 1;
		if (q) { q->reserve(qp+1); q->size = qp; }

		for (int up = u.size-1; --qp >= 0; up--) {
			c = (((uint64)u.data[up+1]) << 32) | (uint64)u.data[up];
			g = c / (uint64)vh;
			if (g > 0xFFFFFFFFULL) g = 0xFFFFFFFFULL;

			while ((c - g*vh) < 0x100000000ULL &&
				(((c - g*vh) << 32) + u.data[up-1]) < (g*(uint64)vh2))
				g--;

			c = 0;
			for (int i = qp, j = 0; j <= n; i++, j++) {
				c += g * (uint64)v.data[j];
				if (u.data[i] >= (unsigned)(c & 0xFFFFFFFFULL)) {
					u.data[i] -= (unsigned)(c & 0xFFFFFFFFULL);
					c >>= 32;
				} else {
					u.data[i] += (unsigned)(0x100000000ULL - (c & 0xFFFFFFFFULL));
					c = (c >> 32) + 1;
				}
			}

			if (c != 0) {
				g--;
				assert(c == 1);
				c = 0;
				for (int i = qp, j = 0; j <= n; i++, j++, c >>= 32) {
					c += (uint64)u.data[i] + (uint64)v.data[j];
					u.data[i] = (unsigned)c;
				}
				assert(c == 1);
			}

			if (q) q->data[qp] = (unsigned)g;
		}

		u >>= d;
		v >>= d;
		if (q) q->normalize();
	}

public:
	static int cmp(const BigInt &x, const BigInt &y) {
		if (x.size != y.size) return sgn(x.size - y.size);
		return absCmp(x, y) * (x.size < 0 ? -1 : 1);
	}

	static int cmp1s(const BigInt &x, int y) {
		if (y == 0) return sgn(x.size);
		if (y > 0) {
			if (x.size <= 0) return -1;
			if (x.size > 1) return +1;
			if (x.data[0] == (unsigned)y) return 0;
			return x.data[0] > (unsigned)y ? +1 : -1;
		} else {
			if (x.size >= 0) return +1;
			if (x.size < -1) return -1;
			if (x.data[0] == (unsigned)(-y)) return 0;
			return x.data[0] > (unsigned)(-y) ? -1 : +1;
		}
	}

	static void add(BigInt &z, const BigInt &x, const BigInt &y) {
		add(z, x, +1, y);
	}

	static void sub(BigInt &z, const BigInt &x, const BigInt &y) {
		add(z, x, -1, y);
	}

	static void mul(BigInt &z, const BigInt &x, const BigInt &y) {
		if (max(abs(x.size), abs(y.size)) < 64)
			mulQuadratic(z, x, y);
		else
			mulKaratsuba(z, x, y);
	}

	static void mod(BigInt &r, const BigInt &u, const BigInt &v) {
		r = u;
		absDiv(NULL, r, v);
	}

	static void div(BigInt &q, BigInt &r, const BigInt &u, const BigInt &v) {
		int us = sgn(u.size), vs = sgn(v.size);

		r = u;
		absDiv(&q, r, v);

		//TODO
		if (us*vs < 0) q.size = -q.size;
	}

	void assign(int n) { reserve(1); size = sgn(n); data[0] = abs(n); }

	void assign(long long n) {
		reserve(2);
		if (n < 0) { size = -2; n = -n; } else { size = 2; }
		data[0] = (unsigned)(n & 0xFFFFFFFFU);
		data[1] = (unsigned)(n >> 32);
		normalize();
	}

	void assign(const BigInt &b) {
		if (this == &b) return;
		int n = abs(b.size);
		reserve(n);
		size = b.size;
		memcpy(data, b.data, n * sizeof(unsigned));
	}

	void assign(const char *s, int radix = 10) {
		assert(2 <= radix && radix <= 36);

		while (isspace(*s)) s++;
		int sign = 1;
		if (*s == '+') { s++; } else if (*s == '-') { s++; sign = -1; }
		while (*s == '0') s++;

		int n = 0;
		for (n = 0; s[n] && isalnum(s[n]); n++);

		size = 0;
		if (n > 20)
			reserve((int)(log((double)radix)/log(2.0)/32.0*n) + 2);
		else
			reserve(n/9+2);

		unsigned a = 0, m = 1;
		for (int i = 0; i < n; i++) {
			int dig = (isdigit(s[i]) ? (s[i]-'0') : (toupper(s[i])-'A'+10));
			assert(dig < radix);

			a = a * radix + dig;
			m *= radix;
			if (m > 0x3000000) { absMulAdd1(*this, *this, m, a); a = 0; m = 1; }
		}
		if (m > 1) absMulAdd1(*this, *this, m, a);

		size *= sign;
	}

	BigInt(int n = 0) { data = NULL; assign(n); }
	BigInt(int n, int cap) { data = NULL; reserve(cap); assign(n); }
	BigInt(long long n) { data = NULL; assign(n); }
	BigInt(const BigInt &b) { data = NULL; assign(b); }
	BigInt(const char *s, int radix = 10) { data = NULL; assign(s, radix); }
	BigInt(const string &s, int radix = 10) { data = NULL; assign(s.c_str(), radix); }

	BigInt &operator =(int n) { assign(n); return *this; }
	BigInt &operator =(long long n) { assign(n); return *this; }
	BigInt &operator =(const BigInt &b) { assign(b); return *this; }
	BigInt &operator =(const char *s) { assign(s); return *this; }
	BigInt &operator =(const string &s) { assign(s.c_str()); return *this; }
	BigInt &operator +=(const BigInt &y) { add(*this, *this, +1, y); return *this; }
	BigInt &operator -=(const BigInt &y) { add(*this, *this, -1, y); return *this; }
	BigInt &operator *=(const BigInt &y) { mul(*this, *this, y); return *this; }
	BigInt &operator /=(const BigInt &y) { BigInt q, r; div(q, r, *this, y); assign(q); return *this; }
	BigInt &operator %=(const BigInt &y) { mod(*this, *this, y); return *this; }
	BigInt &operator +=(int y) { add1s(*this, *this, y); return *this; }
	BigInt &operator -=(int y) { add1s(*this, *this, -y); return *this; }
	BigInt &operator *=(int y) { mul1s(*this, *this, y); return *this; }
	BigInt &operator <<=(int n) { shl(n); return *this; }
	BigInt &operator >>=(int n) { shr(n); return *this; }
	void operator ++() { add1s(*this, *this, 1); }
	void operator --() { add1s(*this, *this, -1); }
	BigInt operator -() { BigInt z = *this; z.negate(); return z; }
	BigInt operator >>(int n) const { BigInt r = *this; r.shr(n); return r; }
	BigInt operator <<(int n) const { BigInt r = *this; r.shl(n); return r; }

	string str(int radix = 10) const {
		assert(2 <= radix && radix <= 36);

		if (size == 0) return "0";

		int y = 1, m = 0;
		while (y < 0x300000) { y *= radix; m++; }

		BigInt x(*this);
		x.size = abs(x.size);

		char *tmp = (char *)malloc(x.size*(radix>=10?10:32)+10);
		int n = 0;

		while (x.size != 0) {
			unsigned r = absDiv1(x, x, y);
			for (int i = 0; i < m; i++, r /= radix)
				tmp[n++] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[r % radix];
		}

		while (n > 0 && tmp[n-1] == '0') n--;
		if (size < 0) tmp[n++] = '-';
		reverse(tmp, tmp+n);
		tmp[n] = 0;

		string res = string(tmp);
		free(tmp);
		return res;
	}

	string toString(int r = 10) const { return str(r); }
	int toInt() const { return sgn(size) * (int)data[0]; }
	long long toLL() const {
		long long r = 0;
		for (int i = 0; i < 2 && i < abs(size); i++) r = (r << 32) | data[i];
		return size < 0 ? -r : r;
	}

	void setBit(int n) {
		int s = abs(size), m = (n>>5)+1;
		reserve(m);
		while (s < m) data[s++] = 0;
		size = (size < 0 ? -s : s);
		data[n>>5] |= 1U << (n & 31);
	}

	void clrBit(int n) { if (abs(size) > (n>>5)) { data[n>>5] &= ~(1U << (n & 31)); normalize(); } }
	int getBit(int n) const { return (abs(size) > (n>>5)) ? ((data[n>>5]>>(n&31))&1) : 0; }

	// Returns 1+(index of highest non-zero bit)
	int bitSize() const {
		if (size == 0) return 0;
		int n = (abs(size) - 1) * 32;
		unsigned t = data[abs(size)-1];
		if (t >= 65536) { n += 16; t >>= 16; }
		if (t >= 256) { n += 8; t >>= 8; }
		if (t >= 16) { n += 4; t >>= 4; }
		if (t >= 4) { n += 2; t >>= 2; }
		if (t >= 2) { n++; t >>= 1; }
		if (t >= 1) n++;
		return n;
	}

	void shl(int s) {
		if (size == 0) return;
		if (s < 0) shr(-s);

		int n = abs(size), w = s >> 5;
		reserve(n + w + 1);

		if (w > 0) {
			for (int i = n-1; i >= 0; i--) data[i+w] = data[i];
			for (int i = w-1; i >= 0; i--) data[i] = 0;
			n += w;
		}

		s &= 31;
		if (s > 0) {
			unsigned a = 0, b;
			data[n++] = 0;
			for (int i = 0; i < n; i++) {
				b = data[i] >> (32 - s);
				data[i] = (data[i] << s) | a;
				a = b;
			}
		}

		size = (size < 0 ? -n : n);
		normalize();
	}

	void shr(int s) {
		if (s < 0) shl(-s);

		int n = abs(size), w = s >> 5;
		if (w > 0) {
			for (int i = 0; i+w < n; i++) data[i] = data[i+w];
			n -= w;
			if (n < 0) n = 0;
		}

		s &= 31;
		if (s > 0) {
			unsigned a = 0, b;
			for (int i = n-1; i >= 0; i--) {
				b = data[i] << (32 - s);
				data[i] = (data[i] >> s) | a;
				a = b;
			}
		}

		size = (size < 0 ? -n : n);
		normalize();
	}

	void negate() { size = -size; }
	int sign() const { return sgn(size); }
	int compareTo(const BigInt &y) const { return cmp(*this, y); }
	int compareTo(int y) const { return cmp1s(*this, y); }
};

BigInt operator +(const BigInt &x, const BigInt &y) { BigInt z; BigInt::add(z, x, y); return z; }
BigInt operator -(const BigInt &x, const BigInt &y) { BigInt z; BigInt::sub(z, x, y); return z; }
BigInt operator *(const BigInt &x, const BigInt &y) { BigInt z; BigInt::mul(z, x, y); return z; }
BigInt operator /(const BigInt &x, const BigInt &y) { BigInt q, r; BigInt::div(q, r, x, y); return q; }
BigInt operator %(const BigInt &x, const BigInt &y) { BigInt r; BigInt::mod(r, x, y); return r; }
bool operator ==(const BigInt &x, const BigInt &y) { return BigInt::cmp(x, y) == 0; }
bool operator ==(const BigInt &x, int y) { return BigInt::cmp1s(x, y) == 0; }
bool operator !=(const BigInt &x, const BigInt &y) { return BigInt::cmp(x, y) != 0; }
bool operator <(const BigInt &x, const BigInt &y) { return BigInt::cmp(x, y) < 0; }
bool operator <=(const BigInt &x, const BigInt &y) { return BigInt::cmp(x, y) <= 0; }
bool operator >(const BigInt &x, const BigInt &y) { return BigInt::cmp(x, y) > 0; }
bool operator >=(const BigInt &x, const BigInt &y) { return BigInt::cmp(x, y) >= 0; }
namespace std { template<> inline void swap(BigInt &a, BigInt &b) { a.swap(b); } }

typedef long long ll;
ll fact[32];
BigInt big_fact[32];

struct seq {
	int data[22], n;
	seq() { n = 0; }
	int &operator[](int i) { return data[i]; }
	void operator +=(int x) { data[n++] = x; }
	void sort() { std::sort(data, data+n); }
	void relabel(int *cnt = NULL, int *orig = NULL) {
		int tmp[32];
		if (orig == NULL) orig = tmp;
		for (int i = 0; i < n; i++) orig[i] = data[i];
		std::sort(orig, orig+n);
		std::unique(orig, orig+n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; ; j++) {
				if (data[i] == orig[j]) {
					data[i] = j;
					break;
				}
			}
		}
		if (cnt != NULL) {
			for (int i = 0; i < n; i++) cnt[i] = 0;
			for (int i = 0; i < n; i++) cnt[data[i]]++;
		}
	}
	void restore(int *orig) {
		for (int i = 0; i < n; i++) data[i] = orig[data[i]];
	}
};

seq read() {
	seq s;

	char c;
	scanf(" %c", &c);
	assert(c == '{' || c == '(');

	int x;
	while (scanf(" %d , ", &x) == 1)
		s += x;

	scanf(" %c", &c);
	assert(c == '}' || c == ')');

	return s;
}

void print(seq s, bool multiset = false) {
	if (multiset) s.sort();
	printf(multiset ? "(" : "{");
	for (int i = 0; i < s.n; i++)
		printf(i==0 ? "%d" : ",%d", s[i]);
	printf(multiset ? ")\n" : "}\n");
}

string readWord() {
	char s[100] = {0};
	if (scanf(" %[a-zA-Z]", s) != 1)
		return "";
	return string(s);
}
long long readLL() { long long x; scanf("%lld", &x); return x; }
BigInt readBig() { char s[100]; scanf(" %[0-9]", s); return BigInt(s); }

ll nperm(int cnt[], int k) {
	ll a = 1;
	int sum = 0;
	for (int i = 0; i < k; i++) {
		a *= fact[cnt[i]];
		sum += cnt[i];
	}
	return fact[sum] / a;
}

seq degrade(seq s) { s.sort(); return s; }
seq promote(seq s, ll num) {
	int cnt[32], orig[32];
	s.sort();
	s.relabel(cnt, orig);

	seq res;
	for (int pos = 0; pos < s.n; pos++) {
		int x;
		for (x = 0; x < s.n; x++) {
			if (cnt[x] == 0) continue;
			cnt[x]--;
			ll t = nperm(cnt, s.n);
			if (num >= t)
				num -= t;
			else
				break;
			cnt[x]++;
		}
		res += x;
	}

	res.restore(orig);
	return res;
}

ll rank(seq s) {
	int cnt[32];
	s.relabel(cnt);

	ll res = 0;
	for (int pos = 0; pos < s.n; pos++) {
		for (int x = 0; x < s[pos]; x++) {
			if (cnt[x] == 0) continue;
			cnt[x]--;
			res += nperm(cnt, s.n);
			cnt[x]++;
		}
		cnt[s[pos]]--;
	}
	return res;
}

map<string, BigInt> dc_memo;

BigInt &deriveCount(int cnt[], int n, int m) {
	string key;
	for (int i = 0; i < n; i++)
		if (cnt[i] > 0) key += 'a'+cnt[i];
	sort(key.begin(), key.end());
	key += 'a' + m;

	if (dc_memo.count(key) > 0) return dc_memo[key];

	static BigInt f[32][32];
	for (int i = 0; i <= m; i++) f[n][i] = 0;
	f[n][0] = big_fact[m];
	for (int i = n-1; i >= 0; i--) {
		f[i][0] = fact[m];
		for (int j = 1; j <= m; j++) {
			f[i][j] = 0;
			for (int k = 0; k <= j && k <= cnt[i]; k++)
				f[i][j] += f[i+1][j-k]/big_fact[k];
		}
	}

	return dc_memo[key] = f[0][m];
}

seq derive(seq s, int m, BigInt num) {
	int cnt[32], orig[32];
	s.sort();
	s.relabel(cnt, orig);

	seq res;
	for (int pos = 0; pos < m; pos++) {
		int x;
		for (x = 0; x < s.n; x++) {
			if (cnt[x] <= 0) continue;
			cnt[x]--;
			BigInt t = deriveCount(cnt, s.n, m-pos-1);
			if (num >= t)
				num -= t;
			else
				break;
			cnt[x]++;
		}
		res += x;
	}
	res.restore(orig);
	return res;
}

BigInt underive(seq dst, seq src) {
	int cnt[32], orig[32];
	src.sort();
	src.relabel(cnt, orig);

	for (int i = 0; i < dst.n; i++) {
		int j;
		for (j = 0; j < src.n && orig[j] != dst[i]; j++);
		dst[i] = j;
	}

	BigInt res = 0;
	for (int pos = 0; pos < dst.n; pos++) {
		for (int x = 0; x < dst[pos]; x++) {
			if (cnt[x] <= 0) continue;
			cnt[x]--;
			res += deriveCount(cnt, src.n, dst.n-1-pos);
			cnt[x]++;
		}
		cnt[dst[pos]]--;
	}
	return res;
}

int main() {
	fact[0] = 1;
	for (int n = 1; n <= 30; n++)
		fact[n] = fact[n-1] * n;

	big_fact[0] = 1;
	for (int n = 1; n <= 30; n++)
		big_fact[n] = big_fact[n-1] * n;

	for (;;) {
		string op = readWord();
		if (op == "" || op == "end") break;

		if (op == "degrade") {
			print(degrade(read()), true);
		} else if (op == "promote") {
			seq s = read();
			print(promote(s, readLL()));
		} else if (op == "rank") {
			printf("%lld\n", rank(read()));
		} else if (op == "derive") {
			seq s = read();
			int m = readLL();
			BigInt num = readBig();
			print(derive(s, m, num));
		} else if (op == "find") {
			seq s = read();
			seq t = read();
			printf("%s\n", underive(s, t).str().c_str());

			//printf("derive "); print(t); printf(" %d %s\n", s.n, underive(s, t).str().c_str());
		}
	}
}
