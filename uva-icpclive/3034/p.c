#include <stdio.h>

static int isqrt(int a)
{
	int x, y;

	for (x = a; x > 0; x = y)
		if ((y = ((x + (a / x)) >> 1)) >= x) return x;

	return 0;
}

int main()
{
	int n, r, c;

	while (scanf("%u", &n) == 1) {
		r = (isqrt(8 * n - 7) - 1) >> 1;
		c = n - ((r * (r + 1)) >> 1) - 1;

		if (r & 1)
			printf("TERM %d IS %d/%d\n", n, c + 1, r + 1 - c);
		else
			printf("TERM %d IS %d/%d\n", n, r + 1 - c, c + 1);
	}

	return 0;
}
