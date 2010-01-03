#include <stdio.h>
#include <math.h>

unsigned gen(unsigned s, long double *r)
{
    static const long double Z = (long double)1.0 / (1LL<<32);
    unsigned a = s >> 16, b = s & 0xFFFF;
    *r = ((unsigned long long)s * (unsigned long long)s) * Z;
    return ((a * a) << 16) + 2 * a * b + ((b * b) >> 16);
}

void cyc(int n, unsigned s)
{
	unsigned s1, s2, i, j, k;
	long double m1, m2, x;

	for (s1 = s2 = s, i = j = 0, m1 = m2 = 0.; j < n; i++, j++) {
		if (s1 == s2 && i != j) {
			printf("cycle i=%d j=%d s=%.8X\n", i, j, s1);
			break;
		}

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
		printf("no cycle; m=%.10Lf\n", m2);
		return;
	}

	k = (n - j) / (j - i);
	m2 += k * (m2 - m1);
	j += k * (j - i);

	for (; j < n; j++) {
		s2 = gen(s2, &x);
		m2 += x;
	}

	m2 /= (long double)n;
	printf("m=%.10Lf\n", m2);
}

long double solve(int n, unsigned s)
{
	long double m, d, x;
	unsigned t;
	int i;

	cyc(n, s);

	for (m = 0, t = s, i = 0; i < n; i++) {
		t = gen(t, &x);
		m += x;
	}
	m /= (long double)n;
printf("M=%.10Lf\n",m);

	for (d = 0, t = s, i = 0; i < n; i++) {
		t = gen(t, &x);
		x -= m;
		d += x * x;
	}
	d /= (long double)n;

	return (long double)sqrt(d);
}

int main()
{
	int n, c, t;
	unsigned long long s;

	for (scanf("%d", &t), c = 1; c <= t && scanf("%d %llu", &n, &s) == 2; c++)
		printf("Case #%d: %.5Lf\n", c, solve(n, (s >> 16) & 0xFFFFFFFF));

	return 0;
}
