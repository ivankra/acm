// MST
#include <stdio.h>
#include <math.h>

#define SQ(x) ((x) * (x))

int main()
{
	static double x[128], y[128], d[128], r;
	static int c[128], m, n, t;
	int i, k;
	double u;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (i = 0; i < n; i++)
			scanf("%lf %lf", &x[i], &y[i]);

		for (i = 0; i < n; i++)
			c[i] = 0;

		for (c[0] = 1, i = 1; i < n; i++)
			d[i] = SQ(x[i] - x[0]) + SQ(y[i] - y[0]);

		for (r = 0., m = n - 1; m > 0; m--) {
			for (i = 1, k = 0; i < n; i++)
				if (c[i] == 0 && (k == 0 || d[i] < d[k]))
					k = i;

			r += sqrt(d[k]);
			c[k] = 1;

			for (i = 1; i < n; i++) {
				if (c[i]) continue;
				u = SQ(x[i] - x[k]) + SQ(y[i] - y[k]);
				if (d[i] > u) d[i] = u;
			}
		}

		printf(t ? "%.2f\n\n" : "%.2f\n", r);
	}

	return 0;
}
