#include <stdio.h>
#include <string.h>

int primes[664580], nprimes;
unsigned sieve[320000];

#define GET(b) ((sieve[(b) >> 5] >> ((b) & 31)) & 1)
#define ISPRIME(p) (p == 2 || (p > 2 && (p & 1) != 0 && (GET((p - 1) >> 1) == 0)))

void make()
{
	register int i, j, k;

	memset(sieve, 0, sizeof(sieve));
	for (k = 1; k < 1581; k++) {
		if (GET(k)) continue;
		for (j = 2 * k + 1, i = 2 * k * (k + 1); i < 5000000; i += j)
			sieve[i >> 5] |= 1 << (i & 31);
	}

	nprimes = 1;
	primes[0] = 2;

	for (i = 1; i < 5000000; i++)
		if (GET(i) == 0) primes[nprimes++] = 2 * i + 1;
}

int main()
{
	int i;

	make();

	printf("nprimes=%d\n", nprimes);
	for (i = 0; i < 12; i++)
		printf("%d\n", primes[i]);
	printf("prime[12345] = %d  (==132241)\n", primes[12345-1]);

	return 0;
}
