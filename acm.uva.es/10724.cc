#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#define EPS 1e-8

double x[64], y[64], d[64][64], w[64][64], bc;
int e[64][64], n, bu, bv;

void sol()
{
	int u, v, i, j;
	double c, t;

	for (u = 0; u < n; u++) {
		for (v = u + 1; v < n; v++) {
			if (e[u][v]) continue;

			c = 0.;
			for (i = 0; i < n; i++)
				for (j = i+1; j < n; j++) {
					t = d[i][j];
					t <?= d[i][u]+w[u][v]+d[v][j];
					t <?= d[i][v]+w[v][u]+d[u][j];
					c += d[i][j] - t;
				}

//			c *= 2.;

			if (c > bc+EPS ||
			    (fabs(c-bc) < EPS && w[u][v]<w[bu][bv]-EPS))
				{ bc=c; bu=u; bv=v; }
		}
	}
}

int main()
{
	int i, j, k, m, a, b;

	while (scanf("%d %d", &n, &m) == 2) {
		if (n == 0 && m == 0) break;
		assert(n > 0 && m > 0 && n < 60);

		for (i = 0; i < n; i++)
			scanf("%lf %lf", &x[i], &y[i]);

		for (i = 0; i < n; i++) {
			for (j = i+1; j < n; j++) {
				w[i][j] = w[j][i] = sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
				e[i][j] = e[j][i] = 0;
				d[i][j] = d[j][i] = 1e99;
			}
			e[i][i] = 1; d[i][i] = w[i][i] = 0.;
		}

		while (m-- > 0 && scanf("%d %d", &a, &b) == 2) {
			assert(1<=a&&a<=n && 1<=b&&b<=n);
			a--; b--; e[a][b]=e[b][a]=1; d[a][b]=d[b][a]=w[a][b];
		}

		for (k = 0; k < n; k++)
			for (i = 0; i < n; i++)
				for (j = 0; j < n; j++)
					d[i][j] <?= d[i][k] + d[k][j];

		bc = 0.;
		sol();
		printf(bc<1.+EPS ? "No road required\n" : "%d %d\n", bu+1,bv+1);
	}

	return 0;
}
