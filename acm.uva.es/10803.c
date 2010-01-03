#include <stdio.h>
#include <math.h>

int main()
{
	static double d[128][128], r;
	static int c[128][128], x[128], y[128], t, m, n;
	register int i, j, k;

	for (scanf("%d", &m), t = 1; t <= m && scanf("%d", &n) == 1; t++) {
		for (i = 0; i < n; i++)
			scanf("%d %d", &x[i], &y[i]);

		for (i = 0; i < n; i++) {
			for (j = 0; j < i; j++) {
				d[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) +
					       (y[i] - y[j]) * (y[i] - y[j]));
				d[j][i] = d[i][j];

				if (d[i][j] < (10.0 + 10e-9))
					c[i][j] = c[j][i] = 1;
				else
					c[i][j] = c[j][i] = 0;
			}

			d[i][i] = 0;
			c[i][i] = 1;
		}

		for (k = 0; k < n; k++) {
			for (i = 0; i < n; i++) {
				if (i == k || c[i][k] == 0)
					continue;

				for (j = 0; j < i; j++) {
					if (c[k][j] == 0)
						continue;

					if (c[i][j] != 0 &&
					    (d[i][k] + d[k][j]) > d[i][j])
						continue;

					d[i][j] = d[j][i] = d[i][k] + d[k][j];
					c[i][j] = c[j][i] = 1;
				}
			}
		}

		for (i = 0, r = 0.; i < n; i++) {
			for (j = 0; j < i; j++) {
				if (c[i][j] == 0) break;
				if (d[i][j] > r) r = d[i][j];
			}
			if (j < i) break;
		}

		printf("Case #%d:\n", t);

		if (i < n)
			printf("Send Kurdy\n\n");
		else
			printf("%.4f\n\n", r);
	}

	return 0;
}
