#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int primes[664580], nprimes;
unsigned sieve[320000];

#define GET(b) ((sieve[(b) >> 5] >> ((b) & 31)) & 1)

int isprime(int p)
{
	return (p == 2 || ((p & 1) != 0 && GET((p - 1) >> 1) == 0));
}

void make()
{
	int i, j, k;

	memset(sieve, 0, sizeof(sieve));
	for (k = 1; k < 1581; k++) {
		if (GET(k)) continue;
		for (j = 2 * k + 1, i = 2 * k * (k + 1); i < 5000000; i += j)
			sieve[i >> 5] |= 1 << (i & 31);
	}

	for (primes[0] = 2, nprimes = i = 1; i < 5000000; i++)
		if (GET(i) == 0) primes[nprimes++] = 2 * i + 1;
}

char *goldbach(int n)
{
	static char *gtab[320] = { "?" };
	int p;

	if (gtab[0] != NULL)
		memset(gtab, 0, sizeof(gtab));

	/*assert(2 <= n && n <= 310 && (n % 2) == 0);*/

	if (gtab[n] == NULL) {
		for (p = 0; !isprime(n - primes[p]); p++);
		sprintf(gtab[n] = (char *)malloc(20), "%d %d", primes[p], n - primes[p]);
	}

	return gtab[n];
}

/* Finds greatest prime p, s.t. p <= m */
int find(int m)
{
	int a, b, c;

	for (a = 0, b = nprimes - 1; (b - a) > 1;) {
		if (primes[c = (a + b) >> 1] > m)
			b = c - 1;
		else
			a = c;
	}

	return primes[(primes[b] <= m) ? b : a];
}

int main()
{
	int n, t;

	for (make(); scanf("%d", &n) == 1;) {
		if (n < 8) {
			printf("Impossible.\n");
		} else if ((n & 1) == 1) {
			t = find(n - 6);
			printf("2 %d %s\n", t, goldbach(n - t - 2));
		} else {
			t = find((n - 4) / 2);
			printf("%d %d %s\n", t, t, goldbach(n - 2 * t));
		}
	}

	return 0;
}
