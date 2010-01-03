#include <stdio.h>
#include <string.h>

int sieve[16384], prime[16384];

int main()
{
	int x, y, yr, r, p, n, t;

	memset(sieve, 0, sizeof(sieve));
	for (x = 2; x <= 10000; x++)
		if (sieve[x] == 0)
			for (y = x * x; y <= 10000; y += x) sieve[y] = 1;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (y = -1, x = 2; x <= n; x++) {
			if (sieve[x]) continue;

			p = n / x;
			r = n - p * x;

			if (y < 2 || r > yr) {
				y = x;
				yr = r;
			}
		}

		printf("%d\n", y);
	}

	return 0;
}
