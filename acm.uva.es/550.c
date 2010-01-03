#include <stdio.h>
#include <assert.h>

typedef unsigned long long ull;

ull gcd(ull x, ull y)
{
	return (y == 0) ? x : gcd(y, x % y);
}

/* a^x = b (mod m) */
ull solve(ull a, ull b, ull m)
{
	ull x = 0, t = 1;
	for (a %=m, b %= m; t != b; x++, t = (t * a) % m);
	return x;
}

int main()
{
	ull b, l, k, m;

	while (scanf("%llu %llu %llu", &b, &l, &k) == 3) {
		if (l == 0 || k <= 1) {
			printf("1\n");
		} else {
			m = (b * k - 1) / gcd(b * k - 1, l);
			printf("%llu\n", solve(b, k, m) + 1);
		}
	}

	return 0;
}
