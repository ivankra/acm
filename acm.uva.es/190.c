#include <stdio.h>

double hypot(double, double);
double ax, ay, bx, by, cx, cy, x, y, r;

void find()
{
	double s1, s2, s3, t1, t2, t3, d;

	s1 = 2. * ax - 2 * bx;
	s2 = 2 * ay - 2 * by;
	s3 = ax * ax + ay * ay - bx * bx - by * by;

	t1 = 2. * ax - 2 * cx;
	t2 = 2 * ay - 2 * cy;
	t3 = ax * ax + ay * ay - cx * cx - cy * cy;

	d = s1 * t2 - s2 * t1;

	x = (s3 * t2 - s2 * t3) / d;
	y = (s1 * t3 - s3 * t1) / d;

	r = hypot(x - ax, y - ay);
}

char *fmt(double x)
{
	static char buf[16][256];
	static int n = 0;

	n = (n + 1) & 0x0F;

	if (x < 0)
		sprintf(buf[n], "- %.3f", -x);
	else
		sprintf(buf[n], "+ %.3f", x);

	return buf[n];
}

int main()
{
	while (scanf("%lf %lf %lf %lf %lf %lf", &ax, &ay, &bx, &by, &cx, &cy) == 6) {
		find();

		printf(
			"(x %s)^2 + (y %s)^2 = %.3f^2\n"
			"x^2 + y^2 %sx %sy %s = 0\n\n",
			fmt(-x), fmt(-y), r,
			fmt(-2. * x), fmt(-2. * y), fmt(x * x + y * y - r * r)
		);
	}

	return 0;
}
