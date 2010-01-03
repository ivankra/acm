#include <stdio.h>
#include <math.h>

double pi;

double s(double t)
{
	return (1. - 92903950. * cos(t)) / (432000. * sin(t));
}

double inv(double z)
{
	double a, b, c;

	for (a = 0, b = pi;;) {
		c = (a + b) / 2.;
		if ((b - a) < 1e-15)
			return c;

		if (s(c) < z)
			a = c;
		else
			b = c;
	}
}

int main()
{
	double t, v, t0, t1;

	pi = 2. * acos(0.);
	t0 = inv(1.);
	t1 = inv(-1.);
	v = pi / 43200.;

	while (scanf("%lf", &t) == 1) {
		t = t0 - t * v;

		if (t > t0) {
			printf("%f\n", 0.);
		} else if (t < t1) {
			printf("%f\n", 1.);
		} else {
			t = -s(t);
			t = (t * sqrt(1 - t * t) + asin(t)) / pi + 0.5 + 1e-12;
			printf("%f\n", t);
		}
	}

	return 0;
}
