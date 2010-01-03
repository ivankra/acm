#include <stdio.h>

static int isqrt(int a)
{
	register int x, y;

	for (x = a; x > 1; x = y) {
		y = ((x + (a / x)) >> 1);
		if (y >= x) break;
	}

	return x;
}

int main()
{
	int n, r, k, x, y;

	while (scanf("%d", &n) == 1 && n > 0) {
		r = isqrt(n - 1);
		k = n - r * r - 1;

		if (r & 1) {
			x = k;
			y = 2 * r - k;
		} else {
			x = 2 * r - k;
			y = k;
		}

		if (x > r) x = r;
		if (y > r) y = r;

		printf("%d %d\n", x + 1, y + 1);
	}

	return 0;
}
