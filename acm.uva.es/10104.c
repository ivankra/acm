#include <stdio.h>

int egcd(int a, int b, int *x, int *y)
{
	int x1, y1, d;

	if (a < b)
		return egcd(b, a, y, x);

	if (b < 0) {
		d = egcd(a, -b, x, y);
		(*y) *= -1;
		return d;
	}

	if (b == 0) {
		*x = 1;
		*y = 0;
		return a;
	}

	d = egcd(b, a % b, &x1, &y1);
	*x = y1;
	*y = x1 - (a / b) * y1;

	return d;
}

int main()
{
	int a, b, d, x, y;

	while (scanf("%d %d", &a, &b) == 2) {
		d = egcd(a, b, &x, &y);
		printf("%d %d %d\n", x, y, d);
	}

	return 0;
}
