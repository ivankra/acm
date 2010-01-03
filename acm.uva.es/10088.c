#include <stdio.h>

long long gcd(long long x, long long y)
{
	return y ? gcd(y, x % y) : x;
}

long long xabs(long long x)
{
	return (x < 0) ? (-x) : x;
}

int main()
{
	long long x[1024], y[1024], a, b, i, n;

	while (scanf("%lld", &n) == 1 && n > 0) {
		for (i = 0; i < n; i++)
			scanf("%lld %lld", &x[i], &y[i]);

		x[n] = x[0];
		y[n] = y[0];

		for (a = b = 0, i = 0; i < n; i++) {
			a += x[i] * y[i + 1] - x[i + 1] * y[i];
			b += gcd(xabs(x[i + 1] - x[i]), xabs(y[i + 1] - y[i]));
		}

		printf("%lld\n", 1 + (xabs(a) - b) / 2);
	}

	return 0;
}
