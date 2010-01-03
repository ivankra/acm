#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXM 1048576
#define MAXP 1536

static int primes[MAXP], primes2[MAXP], nprimes;
static char sieve[MAXM];

static void make_primes()
{
	register int i, j;

	memset(sieve, 0, sizeof(sieve));

	for (nprimes = 0, i = 2; i < MAXM; i++) {
		if (sieve[i])
			continue;

		if (nprimes < MAXP) {
			primes[nprimes] = i;
			primes2[nprimes] = i * i;
			nprimes++;
		}

		for (j = (i << 1); j < MAXM; j += i)
			sieve[j] = 1;
	}
}

static int isprime(int n)
{
	register int i;

	if (n <= 1) return 0;
	if ((n & 1) == 0) return (n == 2);

	if (n < MAXM) return (sieve[n] == 0);

	i = n % 6;
	if (i != 1 && i != 5) return 0;

	for (i = 1; i < nprimes && primes2[i] <= n; i++)
		if ((n % primes[i]) == 0) return 0;

	return 1;
}

int main()
{
	static int n, found, a, b;
	int d;

	make_primes();

	while (scanf("%d", &n) == 1) {
		if (n & 1) {
			if (n > 4 && isprime(n - 2))
				printf("%d is the sum of 2 and %d.\n", n, n-2);
			else
				printf("%d is not the sum of two primes!\n",n);

			continue;
		}

		for (d = 2, found = 0; d < n; d += 2) {
			a = (n - d) >> 1;
			b = a + d;

			if (a <= 1 || b <= 1)
				continue;

			if (isprime(a) && isprime(b)) {
				found = 1;
				break;
			}
		}

		if (found)
			printf("%d is the sum of %d and %d.\n", n,
			       (a < b) ? a : b, (a > b) ? a : b);
		else
			printf("%d is not the sum of two primes!\n", n);
	}

	return 0;
}
