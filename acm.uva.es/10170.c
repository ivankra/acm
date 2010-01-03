#include <stdio.h>

long long isqrt(long long a)
{
	long long x, y;

	for (x = a; x > 1; x = y) {
		y = (x + (a / x)) >> 1;
		if (y >= x) break;
	}

	return x;
}

int main()
{
	long long s, d, t;

	while (scanf("%lld %lld", &s, &d) == 2) {
		t = (1 - 2 * s + isqrt(4 * s * (s - 1) + 8 * d + 1)) / 2;
		while ((t * (2 * s + t - 1)) < (2 * d)) t++;
		printf("%lld\n", s + t - 1);
	}

	return 0;
}
