#include <stdio.h>

typedef unsigned uint;

uint isqrt(uint a)
{
	uint x, y;

	for (x = a; x > 1; x = y)
		if ((y = ((x + (a / x)) >> 1)) >= x) break;

	return x;
}

uint solve(uint n)
{
	static uint fact[16], nfact;
	uint i, m;

	if (n == 1)
		return 2;

	nfact = 0;
	if ((n & 1) == 0) {
		for (m = 1; (n & 1) == 0; m <<= 1, n >>= 1);
		fact[nfact++] = m;
	}

	for (i = 3, m = isqrt(n) + 1; i <= m; i += 2) {
		if ((n % i) != 0) continue;

		for (m = 1; (n % i) == 0; (m *= i), (n /= i));
		fact[nfact++] = m;

		m = isqrt(n) + 1;
	}

	if (n > 1)
		fact[nfact++] = n;

	for (m = 0, i = 0; i < nfact; i++)
		m += fact[i];

	if (nfact == 1)
		m++;

	return m;
}

int main()
{
	uint t, n;

	for (t = 1; scanf("%u", &n) == 1 && n > 0; t++)
		printf("Case %u: %u\n", t, solve(n));

	return 0;
}
