/* Problem 583. "Prime Factors." */
#include <stdio.h>
#include <stdlib.h>

typedef unsigned long u_long;

u_long isqrt(u_long n)
{
	u_long x = 1, y = 1;
	int i;

	for (i = 0; i < 30 && x; i++, x = y)
		if ((y = ((n / x) + x) >> 2) == x)
			break;

	return x;
}

u_long first(u_long n)
{
	register u_long i, j, m;

	static const u_long s[] = {3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199};
	static const u_long g[] = {
		1, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199  /* 43/210 */
	};
#define PERIOD 210

	if ((n & 1) == 0) return 2;
	if (n == 1) return n;

	for (i = 0; i < (sizeof(s) / sizeof(s[0])); i++)
		if ((n % (s[i])) == 0) return s[i];

	m = isqrt(n) + PERIOD + 1;

	for (i = PERIOD; i < m; i += PERIOD) {
		for (j = 0; j < (sizeof(g) / sizeof(g[0])); j++)
			if ((n % (i+g[j])) == 0) return (i + g[j]);
	}

	return n;
}

void factor(long n)
{
	u_long m, p;
	int c = 0;

	printf("%d =", n);

	if (n < 0) {
		printf(" -1");
		n = -n;
		c++;
	}

	m = (u_long)n;
	for (;;) {
		p = first(m);
		if (p == 1 && c)
			break;
		printf("%s%u", c++ ? " x " : " ", p);
		if (p == m)
			break;
		m /= p;
	}

	printf("\n");
}

int main()
{
	long n;

	while (scanf("%d", &n) == 1 && n != 0)
		factor(n);

	return 0;
}
