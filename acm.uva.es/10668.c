#include <stdio.h>
#include <math.h>

double f(double a, double x)
{
	double r;

	if (x < 0) x = -x;
	if (x < 1e-6) return a;

	r = x / 2 + a * a / (8 * x);
	return 2 * r * asin(a / (2 * r));
}

int main()
{
	double a, b, u, v, x;

	while (scanf("%lf %lf %lf", &a, &u, &v) == 3 && a > -0.1) {
		b = (1 + u * v) * a;

		for (u = 0, v = a / 2; (v - u) > 1e-4;)
			if (f(a, x = (u + v) / 2) < b) u = x; else v = x;

		printf("%.3f\n", (u + v) / 2);
	}

	return 0;
}
