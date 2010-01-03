#include <stdio.h>

unsigned isqrt(unsigned a)
{
	unsigned x, y;

	for (x = a; x > 1; x = y) {
		y = (x + a / x) >> 1;
		if (y >= x) break;
	}

	return x;
}

int check(unsigned r, unsigned b0, unsigned x)
{
	unsigned b;

	if (x < 0 || (x % 2) != 0) return 0;

	b = x / 2;
	if (b < b0) return 2;

	if ((7 * b) > (10 * b0)) return 2;

	return 1;
}

int solve(unsigned r, unsigned b0)
{
	unsigned d, t, x1, x2;
	int r1, r2;

	d = 8 * r + 1;

	t = isqrt(d);
	if ((t * t) != d) return 1;

	x1 = 2 * r + 1 - t;
	x2 = 2 * r + 1 + t;

	r1 = check(r, b0, x1);
	r2 = check(r, b0, x2);

	x1 = x1 / 2 - b0;
	x2 = x2 / 2 - b0;

	if (r1 == 1 && r2 == 1) {
		if (x1 == x2)
			printf("%u\n", x1);
		else if (x1 < x2)
			printf("%u %u\n", x1, x2);
		else
			printf("%u %u\n", x2, x1);
		return 0;
	} else if (r1 == 1) {
		printf("%u\n", x1);
		return 0;
	} else if (r2 == 1) {
		printf("%u\n", x2);
		return 0;
	} else if (r1 == 2 || r2 == 2)
		return 2;
	else
		return 1;
}

int main()
{
	unsigned r, b, a;

	while (scanf("%u %u", &r, &b) == 2 && (r != 0 || b != 0)) {
		a = solve(r, b);
		if (a == 1)
			printf("No. of red balls invalid\n");
		else if (a == 2)
			printf("No. of black balls invalid\n");
	}

	return 0;
}
