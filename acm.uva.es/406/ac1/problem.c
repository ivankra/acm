#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main()
{
	static int sieve[1020], primes[1020], n, c;
	int i, j, k;

	memset(sieve, '\0', sizeof(sieve));
	primes[0] = 1;
	primes[1] = 2;
	for (i = 3, k = 2; i < 1020; i += 2) {
		if (sieve[i] != 0)
			continue;
		for (primes[k++] = i, j = i; j < 1020; j += i)
			sieve[j] = 1;
	}

	while (scanf("%d %d", &n, &c) == 2) {
		printf("%d %d:", n, c);

		for (k = 0; primes[k] <= n; k++);

		if (k & 1) {
			i = (k >> 1) - c + 1;
			j = (c << 1) - 1;
		} else {
			i = (k >> 1) - c;
			j = c << 1;
		}

		if (i < 0) i = 0;

		while (i < k && j-- > 0)
			printf(" %d", primes[i++]);
		printf("\n\n");
	}

	return 0;
}
