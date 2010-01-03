#include <cstdio>
#include <cctype>
#include <cstring>
#include <cassert>
#include <string>
#include <algorithm>
using namespace std;
typedef unsigned long long u64;
#define LIMBS 256

struct Num {
	int sign, n;
	unsigned a[LIMBS];
};

void muladd1(Num &x, unsigned m, u64 c) {
	for (int i = 0; i < x.n; i++, c >>= 32)
		x.a[i] = (unsigned)(c += m * (u64)x.a[i]);
	if (c) x.a[x.n++] = (unsigned)c;
}

void set(Num &x, const char *s) {
	memset(&x, 0, sizeof(Num));
	x.n = 0;
	for (x.sign = 1; *s == '+' || *s == '-'; s++)
		if (*s == '-') x.sign *= -1;
	int a = 0, m = 1;
	for (; *s && isdigit(*s); s++) {
		a = a * 10 + *s - '0';
		m *= 10;
		if (m == 1000000000) { muladd1(x, m, a); a = 0; m = 1; }
	}
	if (m > 1) muladd1(x, m, a);
	if (x.n == 0) x.sign = 1;
}

string toString(Num &x0) {
	static char s[LIMBS*10+1024];
	if (x0.n == 0) return "0";
	Num x = x0;
	char *p=s+sizeof(s)-4;
	for (*p = 0; x.n > 0;) {
		u64 r = 0, dv=1000000000ULL;
		for (int i = x.n-1; i >= 0; i--) {
			r = (r << 32) | (u64)x.a[i];
			x.a[i] = r / dv; r %= dv;
		}
		for (int i = 0; i < 9; i++, r /= 10)
			*--p = '0' + (int)(r % 10);
		while (x.n > 0 && x.a[x.n-1] == 0) x.n--;
	}
	while (*p == '0') p++;
	if (x0.sign < 0) *--p = '-';
	return string(p);
}

int absCmp(const Num &x, const Num &y) {
	if (x.n != y.n) return x.n - y.n;
	for (int i = x.n-1; i >= 0; i--)
		if (x.a[i] != y.a[i]) return (x.a[i] > y.a[i]) ? 1 : -1;
	return 0;
}

void absAdd(Num &x, const Num &y) {
	int i; u64 c = 0;
	while (x.n < y.n) x.a[x.n++] = 0;
	for (i = 0; i < y.n; i++, c >>= 32)
		x.a[i] = (unsigned)(c += x.a[i] + (u64)y.a[i]);
	for (; i < x.n && c > 0; i++, c >>= 32)
		x.a[i] = (unsigned)(c += x.a[i]);
	if (c) x.a[x.n++] = c;
	x.sign = 1;
}

void absSub(Num &x, const Num &y) {
	if (absCmp(x,y)<0) { Num t=y; absSub(t,x); x=t; x.sign=x.n?-1:1; return; }
       	int i; u64 c = 1;
	for (i = 0; i < x.n; i++, c >>= 32)
		x.a[i] = (unsigned)(c += x.a[i] + (u64)((i<y.n?y.a[i]:0) ^ 0xffffffffU));
	x.sign = 1;
	while (x.n > 0 && x.a[x.n-1] == 0) x.n--;
}

void add(Num &x, const Num &y) {
	if (x.sign == y.sign) {
		absAdd(x, y);
		x.sign = y.sign;
	} else if (y.sign < 0) {
		absSub(x, y);
	} else {
		Num t = y;
		absSub(t, x);
		x = t;
	}
	if (x.n == 0) x.sign = 1;
}

void neg(Num &x) { x.sign *= -1; if (x.n == 0) x.sign = 1; }

void mul(Num &x, const Num &y) {
	Num t;
	memset(&t, 0, sizeof(t));
	for (int i = 0; i < x.n; i++) {
		u64 c = 0;
		int k = i;
		for (int j = 0; j < y.n; j++, k++, c >>= 32)
			t.a[k] = (unsigned)(c += t.a[k] + x.a[i] * (u64)y.a[j]);
		for (; c > 0; k++, c >>= 32)
			t.a[k] = (unsigned)(c += t.a[k]);
		if (k > t.n) t.n = k;
	}
	while (t.n > 0 && t.a[t.n-1] == 0) t.n--;
	t.sign = t.n ? x.sign * y.sign : 1;
	x = t;
}

void shl(Num &x) {
	u64 c = 0;
	for (int i = 0; i < x.n; i++, c >>= 32)
		x.a[i] = (unsigned)(c += 2*(u64)x.a[i]);
	if (c) x.a[x.n++] = c;
}

void shr(Num &x) {
	u64 c = 0;
	for (int i = x.n-1; i >= 0; i--) {
		c = (c << 32) | (u64)x.a[i];
		x.a[i] = (unsigned)(c >> 1);
		c &= 1;
	}
	while (x.n > 0 && x.a[x.n-1] == 0) x.n--;
}

void div(Num &q, Num &r, const Num &x0, const Num &y0) {
	r = x0;
	if (absCmp(x0, y0) < 0) { q.n = 0; return; }

	Num y = y0;
	int s = 0;
	while (absCmp(r, y) >= 0) { shl(y); s++; }

	memset(&q, 0, sizeof(Num));
	while (s > 0) {
		shr(y); s--;
		if (absCmp(r, y) < 0) continue;
		absSub(r, y);
                q.a[s >> 5] |= 1U << ((s) & 31);
	}
	for (q.n = x0.n; q.n > 0 && q.a[q.n-1] == 0; q.n--);

	q.sign = q.n ? x0.sign * y0.sign : 1;
	r.sign = 1;
}

int main()
{
	char s1[4096], op[256], s2[4096];
	while (scanf(" %s %s %s", s1, op, s2) == 3) {
		Num a, b;
		set(a, s1);
		set(b, s2);

		switch (op[0]) {
		case '+': add(a, b); break;
		case '-': neg(b); add(a, b); break;
		case '*': mul(a, b); break;
		case '/':
			if (b.n == 0) { printf("IMPOSSIBLE\n"); continue; }
			Num q, r;
			div(q, r, a, b);
			a = q;
			break;
		}

		printf("%s\n", toString(a).c_str());
	}
}
