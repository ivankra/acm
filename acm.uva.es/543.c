#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNUM 1000000
#define IS_PRIME(n) (((sieve[(n) >> 3] >> ((n) & 7)) & 1) == 0)

static unsigned char sieve[256+(MAXNUM/8)];

static void make_primes(void)
{
	register int i, j;
	memset(sieve, 0x55, sizeof(sieve));
	sieve[0] &= ~0x07;
	for (i = 3; i < MAXNUM; i += 2)
		if (((sieve[i >> 3] >> (i & 7)) & 1) == 0)
			for (j = i + i; j < MAXNUM; j += i)
				sieve[j >> 3] |= 1 << (j & 7);
}


int main(void)
{
	register int i, n;
	static int t;

	make_primes();

	while (scanf("%d", &t) == 1 && t >= 6) {
		for (n = t, i = 3;; i += 2) {
			if (IS_PRIME(i) && IS_PRIME(n - i)) {
				printf("%d = %d + %d\n", n, i, n - i);
				break;
			}
		}
	}

	return 0;
}
