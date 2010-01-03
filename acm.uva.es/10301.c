#include <stdio.h>
#include <math.h>

double hypot(double, double);

int main()
{
	static double x[128], y[128], r[128];
	static int a[128][128], c[128], s[128];
	double d;
	int i, j, k, m, n, p, t;

	while (scanf("%d", &n) == 1 && n >= 0) {
		for (i = 0; i < n; i++)
			scanf("%lf %lf %lf", &x[i], &y[i], &r[i]);

		for (i = 0; i < n; i++) {
			for (a[i][i] = 0, j = i + 1; j < n; j++) {
				d = hypot(x[i] - x[j], y[i] - y[j]);
				a[i][j] = a[j][i] = ((fabs(r[i] - r[j]) <= d) && (d <= (r[i] + r[j])));
			}
		}

		for (i = 0; i < n; i++)
			c[i] = 0;

		for (k = 0, m = 0; k < n; k++) {
			if (c[k])
				continue;

			for (c[k] = 1, s[0] = k, t = 1, p = 1; p > 0;) {
				for (i = s[--p], j = 0; j < n; j++) {
					if (a[i][j] && c[j] == 0) {
						c[j] = 1;
						s[p++] = j;
						t++;
					}
				}
			}

			if (t > m)
				m = t;
		}

		printf("The largest component contains %d ring%s.\n", m,
			(m == 1) ? "" : "s");
	}

	return 0;
}
