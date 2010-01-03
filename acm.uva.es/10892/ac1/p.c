#include <stdio.h>
#include <string.h>

unsigned isqrt(unsigned a)
{
	unsigned x, y;

	for (x = a; x > 1; x = y)
		if ((y = (x + (a / x)) >> 1) >= x) break;

	return x;
}

unsigned factorize(unsigned b[], unsigned e[], unsigned x)
{
	unsigned i, m, n = 0;

	if (x == 0)
		return 0;

	if ((x & 1) == 0) {
		for (b[n] = 2, e[n] = 0; (x & 1) == 0; x >>= 1) e[n]++;
		n++;
	}

	for (i = 3, m = isqrt(x) + 1; i <= m; i += 2) {
		if ((x % i) == 0) {
			for (b[n] = i, e[n] = 1, x /= i; (x % i) == 0; e[n]++)
				x /= i;
			n++;
			m = isqrt(x);
		}
	}

	if (x > 1)
		b[n] = x, e[n] = 1, n++;

	return n;
}

unsigned solve(unsigned x)
{
	static unsigned a[128], prm[128], e[128], n;
	unsigned i, r, t;

	n = factorize(prm, e, x);

	for (i = 0; i <= n; i++) a[i] = 0;

	for (r = 0;;) {
		for (t = 1, i = 0; i < n; i++)
			if (a[i] == e[i]) t *= (e[i] + 1);
		r += t;

		for (i = 0; i < n; i++)
			if (++a[i] <= e[i])
				break;
			else
				a[i] = 0;
		if (i >= n) break;
	}

	return (r + 1) >> 1;
}

int main()
{
	unsigned n;

	while (scanf("%u", &n) == 1 && n > 0)
		printf("%u %u\n", n, solve(n));

	return 0;
}
