#include <stdio.h>
#include <math.h>

int main()
{
	static double b[101], c[101], r_big, r, t, in, out, pi;
	static int n;

	c[1] = 1.;
	pi = 2 * acos(0.);
	b[1] = 1.;
	for (n = 2; n <= 100; n++) {
		r = 2. * pi / (double)n;
		c[n] = 1. - (2. / (2. + sqrt(2. * (1 - cos(r)))));
		b[n] = pi * (0.5 - 1. / (double)n);
	}

	while (scanf("%lf %d", &r_big, &n) == 2) {
		r = r_big * c[n];

		if (n <= 2) {
			in = 0.;
		} else {
			t = r_big - r;
			in = (sqrt(t * t - r * r) - b[n] * r) * r * (double)n;
		}

		out = pi * (r_big * r_big - r * r * (double)n) - in;

		printf("%.10f %.10f %.10f\n", r, in, out);
	}

	return 0;
}
