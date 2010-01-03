#include <stdio.h>
#include <math.h>

double hypot(double, double);

static double s;

static unsigned isqrt(unsigned a)
{
	unsigned x, y;

	for (x = a; x > 1; x = y) {
		y = ((x + (a / x)) >> 1);
		if (y >= x) break;
	}

	return x;
}

static void get(int a, double *x, double *y)
{
	int r, c;

	r = isqrt(a);
	c = a - r * r;

	(*x) = 0.5 * (c - r);
	(*y) = (3. * r + 2. - (double)(c & 1)) * s;
}

int main()
{
	double x1, y1, x2, y2;
	int m, n;

	s = sqrt(3.) / 6.;

	while (scanf("%d %d", &m, &n) == 2) {
		get(m, &x1, &y1);
		get(n, &x2, &y2);

		printf("%.3f\n", hypot(x1 - x2, y1 - y2));
	}

	return 0;
}
