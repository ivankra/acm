#include <stdio.h>
#include <math.h>

int main()
{
	double s, b, h, u, pi;
	int t;

	pi = 2. * acos(0.);

	for (scanf("%d", &t); t-- > 0 && scanf("%lf %lf", &b, &h) == 2;) {
		b *= tan(atan(2. * h / b) / 2.);

		for (s = 0.; b > 0.000002;) {
			s += (u = b);
			b *= 1. - u / h;
			h -= u;
		}

		printf("%13.6f\n%s", pi * s, t ? "\n" : "");
	}

	return 0;
}
