#include <stdio.h>

int main()
{
	static double a[32][32][32];
	static int p[32][32][32], s[32];
	double t;
	int i, j, k, m, n;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < i; j++)
				scanf("%lf", &a[0][i][j]);

			a[0][i][i] = 1.;

			for (j = i + 1; j < n; j++)
				scanf("%lf", &a[0][i][j]);
		}

		for (k = 1; k < n; k++) {
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					a[k][i][j] = 0.;

					for (m = 0; m < n; m++) {
						t = a[k - 1][i][m] * a[0][m][j];
						if (a[k][i][j] > t)
							continue;

						a[k][i][j] = t;
						p[k][i][j] = m;
					}
				}
			}

			for (i = 0; i < n; i++)
				if (a[k][i][i] > (1.01 + 1e-9)) break;

			if (i < n)
				break;
		}

		if (k >= n) {
			printf("no arbitrage sequence exists\n");
			continue;
		}

		m = i;

		for (j = 0; k >= 0; i = p[k--][m][i])
			s[j++] = i + 1;
		s[j++] = m + 1;

		while (j-- > 0)
			printf(j ? "%d " : "%d\n", s[j]);
	}

	return 0;
}
