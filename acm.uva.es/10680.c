#include <stdio.h>

int primes[131072];

void sieve()
{
	static unsigned s[16384];
	register int i, j, k;

	for (k = 1; k < 501; k++) {
		if ((s[k >> 5] >> (k & 31)) & 1) continue;
		for (j = 2 * k + 1, i = 2 * k * (k + 1); i < 500000; i += j)
			s[i >> 5] |= 1 << (i & 31);
	}

	for (primes[0] = 2, k = 1, i = 1; i < 500000; i++)
		if (((s[i >> 5] >> (i & 31)) & 1) == 0) primes[k++] = 2 * i + 1;
	primes[k] = 0x7FFFFFFF;
}

int main()
{
	int i, j, n, r;

	sieve();

	while (scanf("%d", &n) == 1 && n > 0) {
		for (r = 1, i = 3; i <= n; i *= 3)
			r = (r * 3) % 10;

		for (i = 3; i < 170 && primes[i] <= n; i++) {
			for (j = primes[i]; j <= n; j *= primes[i])
				r = (r * primes[i]) % 10;
		}

		for (; primes[i] <= n; i++)
			r = (r * primes[i]) % 10;

		for (i = 0, j = 2; j <= n; j *= 2)
			i++;

		for (j = 5; j <= n; j *= 5)
			i--;

		while (i-- > 0)
			r = (r * 2) % 10;

		printf("%d\n", r);
	}

	return 0;
}
