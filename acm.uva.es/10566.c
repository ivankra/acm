#include <stdio.h>
#include <math.h>

double a, b;

double f(double x)
{
	double d = sqrt(a * a - x * x + 1e-12), e = sqrt(b * b - x * x + 1e-12);
	return (d * e / (d + e));
}

int main()
{
	double c, x, y, z;

	while (scanf("%lf %lf %lf", &a, &b, &c) == 3) {
		for (x = 0, y = (a < b) ? a : b; fabs(x - y) > 1e-9;) {
			z = (x + y) / 2;

			if (f(z) > c)
				x = z;
			else
				y = z;
		}

		printf("%.3f\n", (x + y) / 2);
	}

	return 0;
}
