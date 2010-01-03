#include <stdio.h>
#include <math.h>

static int tr(double a, double b, double m, double *r)
{
	double c, s;

	c = (a * a + b * b - 2. * m * m) / 2.;

	if (c < 10e-6 && c > -10e-6)
		c = 0.;
	else if (c < 0.)
		return 1;
	else
		c = sqrt(c);
	c *= 2.;

	s = (a + b + c) / 2.;

	s *= (s - a) * (s - b) * (s - c);
	if (s < 10e-6 && s > -10e-6)
		s = 0.;
	else if (s < 0.)
		return 1;
	else
		s = sqrt(s);

	(*r) += s;
	return 0;
}

int main()
{
	double x, y, z, a;

	while (scanf("%lf%lf%lf", &x, &y, &z) == 3) {
		a = 0.;

		if (tr(x * 2. / 3., y * 2. / 3., z / 3., &a) ||
		    tr(y * 2. / 3., z * 2. / 3., x / 3., &a) ||
		    tr(z * 2. / 3., x * 2. / 3., y / 3., &a)) {
			printf("-1.000\n");
			continue;
		}

		if (a < 10e-3) {
			printf("-1.000\n");
			continue;
		}

		printf("%.3f\n", a);
	}

	return 0;
}
