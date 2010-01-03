#include <stdio.h>

int f(int e, int c, int t)
{
	int r = (c == 0) ? 1 : (c * c - c + 2);
	if (e > 0) r += (2 * c + e - 1) * e * 2 + ((r == 1) ? 1 : 0);
	if (t > 0) r += (2 * (c + e) + t - 1) * t * 3 + ((r == 1) ? 1 : 0);
	return r;
}

int main()
{
	int e, c, t;

	while (scanf("%d %d %d", &e, &c, &t) == 3)
		printf("%d\n", f(e, c, t));

	return 0;
}
