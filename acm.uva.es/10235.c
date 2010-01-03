#include <stdio.h>
#include <string.h>

static char sieve[131072];
#define PRIMEP(n) (((sieve[(n) >> 3] >> ((n) & 7)) & 1) == 0)

static void mksieve()
{
	register int i, j;

	memset(sieve, 0x55, sizeof(sieve));

	for (sieve[0] = 0x53, i = 3; i < 1024; i += 2) {
		if (PRIMEP(i)) {
			for (j = i * i; j < 1048576; j += i)
				sieve[j >> 3] |= 1 << (j & 7);
		}
	}
}

int main()
{
	static int n;
	register int k, m;

	mksieve();

	while (scanf("%d", &n) == 1) {
		if (!PRIMEP(n)) {
			printf("%d is not prime.\n", n);
			continue;
		}

		for (k = n, m = 0; k > 0; k /= 10)
			m = m * 10 + (k % 10);

		if (m != n && PRIMEP(m))
			printf("%d is emirp.\n", n);
		else
			printf("%d is prime.\n", n);
	}

	return 0;
}
