#include <stdio.h>

int main()
{
	long long n, p, x, y;
	int t = 1;

	while (scanf("%lld", &p) == 1 && p > 0) {
		x = (p + 2) / 3;
		y = (p >> 1) - ((p & 1) ^ 1);

		n = (y - x + 1) * (3 * (x + y) - 2 * p + 2) / 2;
		n += ((y - x + 2) / 2) + ((p + 1 - x) & 1);

		printf("Case %d: %lld\n", t++, n / 2);
	}

	return 0;
}
