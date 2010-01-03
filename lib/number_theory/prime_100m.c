#include <stdio.h>
#include <string.h>

unsigned sieve[1562501];

#define GET(b) ((sieve[(b) >> 5] >> ((b) & 31)) & 1)
#define ISPRIME(p) (p == 2 || (p > 2 && (p & 1) != 0 && (GET((p - 1) >> 1) == 0)))

void make()
{
	register int i, j, k;

	memset(sieve, 0, sizeof(sieve));
	for (k = 1; k < 5000; k++) {
		if (GET(k)) continue;
		for (j = 2 * k + 1, i = 2 * k * (k + 1); i < 50000000; i += j)
			sieve[i >> 5] |= 1 << (i & 31);
	}
}

int main()
{
	int i, n;

	make();

	for (n = 0, i = 0; i <= 100000000; i++)
		if (ISPRIME(i)) n++;
	printf("pi(100000000)=%d  [%s]\n", n, (n == 5761455) ? "OK" : "WRONG");

	return 0;
}
