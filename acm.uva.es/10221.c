#include <stdio.h>
#include <math.h>

int main()
{
	static char u[128];
	double a, r, pi;

	pi = 2. * acos(0.);

	while (scanf("%lf %lf %[a-z]", &r, &a, u) == 3) {
		r += 6440;

		if (u[0] == 'd')
			a *= pi / 180.;
		else
			a *= pi / 10800.;

		if (a >= (2. * pi - 1e-12))
			a = fmod(a, 2. * pi);

		if (a < 0.)
			a = 2. * pi - fmod(-a, 2. * pi);

		if (a > (pi - 1e-12))
			a = 2. * pi - a;

		printf("%.6f %.6f\n", a * r, 2. * r * sin(a / 2.));
	}

	return 0;
}
