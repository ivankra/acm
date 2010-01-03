#include <stdio.h>

typedef unsigned long long u_int64_t;

int main()
{
	unsigned a, d, d0, n, t;
	u_int64_t s;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		for (s = 0, d = 2; d < n;) {
			a = (n / d);
			if (a <= 1) break;

			d0 = (n / (a + 1));
			d = (n / a) + 1;

			s += (u_int64_t)(a - 1) * (
				((u_int64_t)(d0 + d) *
				(u_int64_t)(d - d0 - 1)) >> 1);
		}

		printf("Case %u: %lld\n", t, s);
	}

	return 0;
}
