#include <stdio.h>

#define MAXDIV  32768
#define MAXFACT 64

typedef unsigned long u_int32_t;
typedef unsigned long long u_int64_t;

static u_int32_t isqrt(u_int64_t a)
{
	register u_int64_t x, y;

	for (x = a; x > 0; x = y)
		if ((y = (x + (a / x)) >> 1) >= x) return (u_int32_t)x;

	return 0;	
}

static int factor(u_int64_t a, u_int64_t p[], int e[])
{
	register u_int32_t d, m;
	int k;

	if (a <= 1) {
		p[0] = a;
		return 1;
	}

	for (k = 0; (a & 1) == 0; a >>= 1, k++);

	if (k > 0) {
		p[0] = 2;
		e[0] = k;
		k = 1;
	}

	for (m = isqrt(a), d = 3; d <= m; d += 2) {
		if ((a % (u_int64_t)d) != 0)
			continue;

		p[k] = d;
		e[k] = 0;

		do {
			e[k]++;
			a /= (u_int64_t)d;
		} while ((a % (u_int64_t)d) == 0);

		m = isqrt(a);
		k++;
	}

	if (a > 1) {
		p[k] = a;
		e[k++] = 1;
	}

	return k;
}

static int divisors(u_int64_t a, u_int64_t d[])
{
	static u_int64_t p[MAXFACT], r;
	static int e[MAXFACT], c[MAXFACT], n, k;
	register int i, j;

	n = factor(a, p, e);

	for (i = 0; i < n; i++)
		c[i] = 0;

	for (k = 0;;) {
		for (r = 1, i = 0; i < n; i++)
			for (j = 0; j < c[i]; j++) r *= p[i];

		d[k++] = r;

		for (i = 0; i < n && ++c[i] > e[i]; i++)
			c[i] = 0;

		if (i >= n)
			return k;
	}
}

int main()
{
	static long long n, d[MAXDIV], a0, a;
	int i, k, r;

	while (scanf("%lld", &n) == 1) {
		k = divisors(n * (u_int64_t)2, (u_int64_t *)d);

		for (a0 = 0, i = 0, r = 0; i < k; i++) {
			a = (n * (long long)2 / d[i]) - d[i] + 1;

			if (a <= 0 || (a & 1) != 0)
				continue;

			if (r > 0 && a == a0)
				continue;

			r++;
			a0 = a;
		}

		printf("%d\n", r);
	}

	return 0;
}
