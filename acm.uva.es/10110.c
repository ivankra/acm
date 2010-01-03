#include <stdio.h>

static unsigned long int_sqrt(unsigned long n)
{
	register unsigned long x, y;
	for (x = n;; x = y)
		if (x < 1 || (y = (x + (n / x)) >> 1) >= x) return x;
}

static int sigma0_mod2(unsigned long n)
{
	register unsigned long i, j, m;

	m = int_sqrt(n) + 10;
	for (i = 2; n > 1 && i < m && i < n; i += (i == 2) ? 1 : 2) {
		for (j = 0; n > 1 && (n % i) == 0; j++, n /= i);

		if (j > 0) {
			if (j & 1)
				return 0;
			m = int_sqrt(n) + 10;
		}
	}

	if (n > 1)
		return 0;

	return 1;
}

int main()
{
	unsigned long n;

	while (scanf("%u", &n) > 0 && n != 0)
		printf(sigma0_mod2(n) ? "yes\n" : "no\n");

	return 0;
}
