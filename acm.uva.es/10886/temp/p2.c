#include <stdio.h>
#include <math.h>

unsigned seed;

/*
(aW + b)^2 = a^2 W^2 + 2abW + b^2
*/

long double gen()
{
    static const long double Z = (long double)1.0 / (1LL<<32);
    long double r = ((unsigned long long)seed * (unsigned long long)seed) * Z;
    unsigned a, b;
    a = seed >> 16;
    b = seed & 0xFFFF;
    seed = ((a * a) << 16) + 2 * a * b + ((b * b) >> 16);
    return r;
}

long double solve(int n, unsigned s)
{
	long double m, d, t;
	int i;

	seed = s;

	for (m = 0, i = 0; i < n; i++)
		m += gen() / (long double)n;

	seed = s;
	for (d = 0, i = 0; i < n; i++) {
		t = gen() - m;
		d += t * t / (long double)n;
	}

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
