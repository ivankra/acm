#include <stdio.h>
#include <math.h>

double cos_dist(double la1, double lo1, double la2, double lo2)
{
	return (cos(la1) * cos(la2) * cos(lo1 - lo2) + sin(la1) * sin(la2));
}

int main()
{
	double la[1024], lo[1024], a, b, c, pi = 2 * acos(0);
	int i, j, k, n;

	while (scanf("%d", &n) == 1) {
		for (i = 0; i < n; i++) {
			scanf("%lf %lf", &la[i], &lo[i]);
			la[i] *= pi / 180.;
			lo[i] *= pi / 180.;
		}

		for (a = -1./0., i = k = 0; i < n; i++) {
			for (b = 1./0., j = 0; j < n; j++) {
				c = cos_dist(la[i], lo[i], la[j], lo[j]);
				if (c < b) b = c;
			}

			if ((b + 1e-8) > a) {
				a = b;
				k = i;
			}
		}

		printf("%.2f %.2f\n", la[k] * 180. / pi, lo[k] * 180. / pi);
	}

	return 0;
}
