#include <stdio.h>

typedef unsigned long long ull;

static ull isqrt(ull a)
{
	ull x, y;

	for (x = a; x > 0; x = y)
		if ((y = (x + (a / x)) >> 1) >= x) return x;

	return 0;
}

int main()
{
	ull n, r, c;

	while (scanf("%llu", &n) == 1) {
		r = (isqrt(8 * n - 7) - 1) >> 1;
		c = n - ((r * (r + 1)) >> 1) - 1;

		printf("%llu/%llu\n", r + 1 - c, c + 1);
	}

	return 0;
}
