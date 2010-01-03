#include <stdio.h>
#include <math.h>

#define SQ(x) ((x) * (x))

int main()
{
	static int x[256], y[256], d[256][256], n, t;
	register int i, j, k, m;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		for (i = 0; i < n; i++)
			scanf("%d %d", &x[i], &y[i]);

		for (i = 0; i < n; i++) {
			for (j = 0; j < i; j++) {
				d[i][j] = SQ(x[i] - x[j]) + SQ(y[i] - y[j]);
				d[j][i] = d[i][j];
			}
			d[i][i] = 0;
		}

		for (k = 0; k < n; k++) {
			for (i = 0; i < n; i++) {
				for (j = 0; j < i; j++) {
					m = ((d[i][k] > d[k][j]) ?
					     d[i][k] : d[k][j]);

					if (d[i][j] > m)
						d[j][i] = d[i][j] = m;
				}
			}
		}

		printf("Scenario #%d\nFrog Distance = %.3f\n\n",
		       t, sqrt(d[0][1]));
	}

	return 0;
}
