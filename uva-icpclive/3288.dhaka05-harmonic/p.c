#include <stdio.h>

typedef unsigned long long num;

num gcd(num x, num y) { return (y == 0) ? x : gcd(y, x % y); }

int main()
{
	int i, c, t, n;
	num a, b, x;

	for (scanf("%d", &t), c = 1; c <= t && scanf("%d", &n) == 1; c++) {
		a = 0;
		b = 1;

		for (i = 0; i < n && scanf("%llu", &x) == 1; i++) {
			a = a * x + b; b *= x;
			x = gcd(a, b); a /= x; b /= x;
		}

		x = a; a = b; b = x;
		a *= (num)n;
		x = gcd(a, b); a /= x; b /= x;

		printf("Case %d: %llu/%llu\n", c, a, b);
	}

	return 0;
}
