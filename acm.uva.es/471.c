#include <stdio.h>

static int check(unsigned long long x)
{
	register int i, m;

	for (m = 0; x > 0; x /= 10ULL) {
		i = 1 << (int)(x % 10ULL);
		if (m & i)
			return 0;
		m |= i;
	}

	return 1;
}

int main()
{
	long long x, n, d;
	int t;

	for (scanf("%d", &t); t-- > 0 && scanf("%lld", &x) == 1;) {
		for (d = 1; d <= 9876543210ULL; d++) {
			n = x * d;

			if (n > 9876543210ULL)
				break;

			if (check(d) && check(n))
				printf("%lld / %lld = %lld\n", n, d, x);
		}

		if (t > 0)
			printf("\n");
	}

	return 0;
}
