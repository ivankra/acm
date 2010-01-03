#include <stdio.h>

typedef long long llong;

llong n1, n2, c1, c2, n, x0, y0, rx, ry, rz;

void check(llong t)
{
	llong x, y, z;

	x = x0 + t * n2;
	y = y0 - t * n1;
	z = c1 * x + c2 * y;

	if (x >= 0 && y >= 0 && (z < rz || rz < 0))
		rx = x, ry = y, rz = z;
}

void egcd(llong a, llong b, llong *x, llong *y, llong *d)
{
	if (a < 0) {
		egcd(-a, b, x, y, d);
		*x = -(*x);
	} else if (b < 0) {
		egcd(a, -b, x, y, d);
		*y = -(*y);
	} else if (b == 0) {
		*x = 1;
		*y = 0;
		*d = a;
	} else {
		egcd(b, a % b, y, x, d);
		*y -= (a / b) * (*x);
	}
}

int main()
{
	llong d, t;

	while (scanf("%lld", &n) == 1 && n > 0) {
		scanf("%lld %lld %lld %lld", &c1, &n1, &c2, &n2);

		egcd(n1, n2, &x0, &y0, &d);
		if ((n % d) != 0) {
			printf("failed\n");
			continue;
		}

		n1 /= d;
		n2 /= d;
		n /= d;
		x0 *= n;
		y0 *= n;

		rz = -1;
		for (t = -x0 / n2, d = -2; d <= 2; d++)
			check(t + d);

		for (t = y0 / n1, d = -2; d <= 2; d++)
			check(t + d);

		if (rz <= 0)
			printf("failed\n");
		else
			printf("%lld %lld\n", rx, ry);
	}

	return 0;
}
