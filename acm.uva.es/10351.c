#include <stdio.h>
#include <math.h>

int main()
{
	double x, y, z, a, b, c, s, pi;
	int t = 1;

	pi = 2. * acos(0.);

	while (scanf("%lf %lf %lf %lf %lf %lf", &x, &y, &z, &a, &b, &c) == 6) {
		if (x != a) {
			x -= a / 2.;
			s = pi * b * c * (1. - ((x * x) / (a * a / 4.))) / 4.;
		} else if (y != b) {
			y -= b / 2.;
			s = pi * a * c * (1. - ((y * y) / (b * b / 4.))) / 4.;
		} else {
			z -= c / 2.;
			s = pi * a * b * (1. - ((z * z) / (c * c / 4.))) / 4.;
		}

		if (s < 0.)
			s = 0.;

		printf("Set #%d\n%.6f\n", t++, s);
	}

	return 0;
}
