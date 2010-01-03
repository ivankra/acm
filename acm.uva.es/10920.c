#include <stdio.h>
#include <assert.h>

typedef long long num;

num isqrt(num a)
{
	num x, y;
	for (x = a; x > 1; x = y) {
		y = (x + a / x) >> 1;
		if (y >= x) break;
	}
	return x;
}

int main()
{
	num z, n, m, a;

	while (scanf("%lld %lld", &z, &a) == 2 && (z != 0 || a != 0)) {
		assert(0 < z && 0 < a && a <= (z * z));
		assert((z % 2) == 1);

		z = (z + 1) >> 1;

		if (a <= 1) {
			printf("Line = %lld, column = %lld.\n", z, z);
			continue;
		}

		n = (1 + isqrt(a - 1)) >> 1;
		m = 2 * n;
		a -= (2*n - 1) * (2*n - 1) + 1;

		if (a < m) {
			printf("Line = %lld, column = %lld.\n", z+n, z+n-1-a);
		} else if (a < (2 * m)) {
			a -= m;
			printf("Line = %lld, column = %lld.\n", z+n-1-a, z-n);
		} else if (a < (3 * m)) {
			a -= 2 * m;
			printf("Line = %lld, column = %lld.\n", z-n, z-n+1+a);
		} else {
			a -= 3 * m;
			printf("Line = %lld, column = %lld.\n", z-n+1+a, z+n);
		}
	}

	return 0;
}
