#include <stdio.h>

int gcd(int x, int y)
{
	int k;

	if (x > 0 && y > 0)
		for (k = 0; ((x | y) & 1) == 0; x >>= 1, y >>= 1, k++);
	else
		k = 0;

	for (;;) {
		if (x == 0) return (y << k);
		if (y == 0) return (x << k);

		while ((x & 1) == 0) x >>= 1;
		while ((y & 1) == 0) y >>= 1;

		if (x > y)
			x -= y;
		else
			y -= x;
	}
}

int main()
{
	char s[256], t[256], *p;
	int x, y, d, c, n;

	for (scanf("%d", &n), c = 1; c <= n && scanf(" %[01] %[01]", s, t) == 2; c++) {
		for (x = 0, p = s; *p;)
			x = (x << 1) | (*p++ - '0');

		for (y = 0, p = t; *p;)
			y = (y << 1) | (*p++ - '0');

		d = gcd(x, y);

		if (d <= 1)
			printf("Pair #%d: Love is not all you need!\n", c);
		else
			printf("Pair #%d: All you need is love!\n", c);
	}

	return 0;
}
