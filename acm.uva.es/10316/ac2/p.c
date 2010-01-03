#include <stdio.h>
#include <math.h>

int main()
{
	static double x[1024], y[1024], z[1024], la[1024], lo[1024];
	double a, b, c, pi = 2 * acos(0);
	int i, j, k, n;

	while (scanf("%d", &n) == 1) {
		for (i = 0; i < n; i++) {
			scanf("%lf %lf", &la[i], &lo[i]);
			a = la[i] * pi / 180.;
			b = lo[i] * pi / 180.;
			z[i] = sin(a);
			y[i] = cos(a) * sin(b);
			x[i] = cos(a) * cos(b);
		}

		for (a = -1./0., i = k = 0; i < n; i++) {
			for (b = 1./0., j = 0; j < n; j++) {
				c = x[i] * x[j] + y[i] * y[j] + z[i] * z[j];
				if (c < b) b = c;
			}

			if ((b + 1e-8) > a) {
				a = b;
				k = i;
			}
		}

		printf("%.2f %.2f\n", la[k], lo[k]);
	}

	return 0;
}
