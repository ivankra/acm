#include <stdio.h>
#include <math.h>

unsigned f(unsigned s, long double *r)
{
    static const long double Z = (long double)1.0 / (1LL<<32);
    unsigned a = s >> 16, b = s & 0xFFFF;
    *r = ((unsigned long long)s * (unsigned long long)s) * Z;
    return ((a * a) << 16) + 2 * a * b + ((b * b) >> 16);
}

long double solve(int n, unsigned s)
{
	long double m, d, x;
	unsigned t;
	int i;

	for (m = 0, t = s, i = 0; i < n; i++) {
		t = f(t, &x);
		m += x;
	}
	m /= (long double)n;

	for (d = 0, t = s, i = 0; i < n; i++) {
		t = f(t, &x);
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
