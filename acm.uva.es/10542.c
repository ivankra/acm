#include <stdio.h>

typedef long long num;

num labs(num x)
{
	return (x < 0) ? -x : x;
}

num gcd(num x, num y)
{
	int s;

	for (s = 0; ((x | y) & 1) == 0;)
		s++, x >>= 1, y >>= 1;

	for (;;) {
		if (x == 0) return (y << s);
		if (y == 0) return (x << s);

		while ((x & 1) == 0) x >>= 1;
		while ((y & 1) == 0) y >>= 1;

		if (x > y)
			x -= y;
		else
			y -= x;
	}
}

num f(num x[], int d)
{
	num r, g;
	int i, j, k;

	for (i = 0; i < d; i++)
		if (x[i] == 0) return 0;

	for (r = 0, i = 1; (i >> d) == 0; i++) {
		for (g = 0, j = k = 0; j < d; j++)
			if ((i >> j) & 1) k++, g = gcd(g, x[j]);

		if (k & 1)
			r += g;
		else
			r -= g;
	}

	return r;
}

int main()
{
	num x[16], y[16];
	int i, c, d, t;

	for (scanf("%d", &t), c = 1; c <= t && scanf("%d", &d) == 1; c++) {
		for (i = 0; i < d; i++)
			scanf("%lld", &x[i]);

		for (i = 0; i < d; i++)
			scanf("%lld", &y[i]);

		for (i = 0; i < d; i++)
			x[i] = labs(x[i] - y[i]);

		printf("Case %d: %lld\n", c, f(x, d));
	}

	return 0;
}
