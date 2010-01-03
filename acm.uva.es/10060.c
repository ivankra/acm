#include <stdio.h>
#include <math.h>

int main()
{
	double x[3], y[3], a, v, r, h, pi;
	int n;

	pi = 2. * acos(0.);

	while (scanf("%d", &n) == 1 && n > 0) {
		for (v = 0.; n-- > 0;) {
			scanf("%lf %lf %lf", &h, &x[0], &y[0]);

			x[1] = x[0];
			y[1] = y[0];
			a = 0.;

			while (scanf("%lf %lf", &x[2], &y[2]) == 2) {
				a += x[1] * y[2] - x[2] * y[1];

				x[1] = x[2];
				y[1] = y[2];

				if (x[0] == x[2] && y[0] == y[2])
					break;
			}

			v += ((a < 0) ? -a : a) * h / 2.;
		}

		scanf("%lf %lf", &r, &h);

		v /= pi * r * r * h;

		printf("%.0f\n", floor(v + 1e-9));
	}

	return 0;
}
