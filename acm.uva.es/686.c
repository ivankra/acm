#include <stdio.h>

static char sieve[65536];

static void mksieve()
{
	register int i, j;
	
	for (i = 0; i < 65536; i++)
		sieve[i] = 1;

	sieve[0] = sieve[1] = 0;

	for (i = 2; i < 256; i++)
		if (sieve[i])
			for (j = i * i; j < 65536; j += i) sieve[j] = 0;
}


int main()
{
	static int n;
	int i, k;

	mksieve();

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0, k = 0; i < n; i++)
			if (sieve[i]) {
				if ((n - i) < i) break;
				if (sieve[n - i])
					k++;
			}

		printf("%d\n", k);
	}

	return 0;
}
