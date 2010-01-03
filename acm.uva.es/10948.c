#include <stdio.h>
#include <string.h>

int prime[664580], nprime;
unsigned sieve[320000];

#define GET(b) ((sieve[(b) >> 5] >> ((b) & 31)) & 1)
#define ISPRIME(p) (p == 2 || (p > 2 && (p & 1) != 0 && (GET((p - 1) >> 1) == 0)))

void make()
{
	register int i, j, k;

	memset(sieve, 0, sizeof(sieve));
	for (k = 1; k < 520; k++) {
		if (GET(k)) continue;
		for (j = 2 * k + 1, i = 2 * k * (k + 1); i < 500000; i += j)
			sieve[i >> 5] |= 1 << (i & 31);
	}

	nprime = 1;
	prime[0] = 2;

	for (i = 1; i < 500000; i++)
		if (GET(i) == 0) prime[nprime++] = 2 * i + 1;
}

int main()
{
	int i, n;

	make();

	while (scanf("%d", &n) && n > 0) {
		printf("%d:\n", n);

		for (i = 0; i < nprime && prime[i] < n; i++)
			if (ISPRIME(n - prime[i])) {
				if (prime[i] <= (n - prime[i]))
					printf("%d+%d\n", prime[i], n - prime[i]);
				else
					printf("%d+%d\n", n - prime[i], prime[i]);
				goto ok;
			}

		printf("NO WAY!\n");
ok:
	}

	return 0;
}
