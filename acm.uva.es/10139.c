#include <stdio.h>

static int int_sqrt(int n)
{
	register int s, t;

	for (s = n; s != 0; s = t)
		if ((t = (s + (n / s)) >> 1) >= s) return s;

	return 0;
}

/* Returns power of prime p in factorization of n! */
static int fact_pow(int n, int p)
{
	long long t;
	int r;

	for (t = p, r = 0; t <= (long long)n; t *= (long long)p)
		r += ((long long)n) / t;

	return r;
}

static int decide(int f, int n)
{
	int i, j, m;

	if (n == 1)
		return 1;

	m = int_sqrt(n) + 3;

	for (i = 2; i <= m && n > 1; i = (i == 2) ? 3 : (i + 1)) {
		for (j = 0; n > 1 && (n % i) == 0; j++, n /= i);

		if (j == 0)
			continue;

		if (fact_pow(f, i) < j)
			return 0;

		m = int_sqrt(n) + 3;
	}

	if (n > 1 && fact_pow(f, n) < 1)
		return 0;

	return 1;
}

int main()
{
	static int a, b;

	while (scanf("%d %d", &a, &b) == 2) {
		if (decide(a, b))
			printf("%d divides %d!\n", b, a);
		else
			printf("%d does not divide %d!\n", b, a);
	}

	return 0;
}
