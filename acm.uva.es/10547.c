#include <stdio.h>

int main()
{
	unsigned long long a, b, m, n, k;
	int d, t;

	for (t = 1; scanf("%llu %llu %d", &k, &n, &d) == 3; t++) {
		if (k == 0 && n == 0 && d == 0)
			break;

		for (m = 1; d-- > 0; m *= 10ULL);

		for (a = 1, b = (k % m); n > 0; n >>= 1) {
			if (n & 1)
				a = (a * b) % m;

			b = (b * b) % m;
		}

		printf("Case #%d: %llu\n", t, a);
	}

	return 0;
}
