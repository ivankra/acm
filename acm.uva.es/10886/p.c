#include <stdio.h>
#include <math.h>

unsigned gen(unsigned s, long double *r)
{
	static const long double Z = (long double)1.0 / (1LL<<32);
	unsigned a = s >> 16, b = s & 0xFFFF;
	*r = ((unsigned long long)s * (unsigned long long)s) * Z;
	return ((a * a) << 16) + 2 * a * b + ((b * b) >> 16);
}

long double solve(int n, unsigned s)
{
	unsigned s1, s2, i, j, k, st, len;
	long double m1, m2, r, x;

	for (s1 = s2 = s, i = j = 0, m1 = m2 = 0.; j < n; i++, j++) {
		if (s1 == s2 && i != j)
			break;

		s1 = gen(s1, &x);
		m1 += x;

		s2 = gen(s2, &x);
		m2 += x;

		if (++j == n) break;

		s2 = gen(s2, &x);
		m2 += x;
	}

	if (j == n) {
		m2 /= (long double)n;

		for (r = 0, s1 = s, i = 0; i < n; i++) {
			s1 = gen(s1, &x);
			x -= m2;
			r += x * x;
		}

		return (long double)sqrt(r / (long double)n);
	}

	st = i;
	len = j - i;
	k = (n - j) / len;

	for (m2 += k * (m2 - m1), j += k * len; j < n; j++) {
		s2 = gen(s2, &x);
		m2 += x;
	}

	m2 /= (long double)n;

	for (r = 0, s1 = s, i = 0; i < st; i++) {
		s1 = gen(s1, &x);
		x -= m2;
		r += x * x;
	}

	for (m1 = 0., j = 0; j < len; j++) {
		s1 = gen(s1, &x);
		x -= m2;
		m1 += x * x;
	}

	for (r += k * m1, i += k * len; i < n; i++) {
		s1 = gen(s1, &x);
		x -= m2;
		r += x * x;
	}	

	return (long double)sqrt(r / (long double)n);
}

int main()
{
	int n, c, t;
	unsigned long long s;

	for (scanf("%d", &t), c = 1; c <= t && scanf("%d %llu", &n, &s) == 2; c++)
		printf("Case #%d: %.5Lf\n", c, solve(n, (s >> 16) & 0xFFFFFFFF));

	return 0;
}
