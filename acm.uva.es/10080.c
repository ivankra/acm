#include <stdio.h>
#include <string.h>

int adj[256][256], nvert;

int maxflow()
{
	static int p[256], q[256], v[256];
	int i, j, f, qh, qt;

	for (f = 0;; f++) {
		memset(v, 0, sizeof(v));

		for (q[qh = 0] = 0, qt = 1, v[0] = 1; qh < qt && v[1] == 0;) {
			for (i = q[qh++], j = 0; j < nvert; j++) {
				if (adj[i][j] && v[j] == 0) {
					v[j] = 1;
					p[j] = i;
					q[qt++] = j;
				}
			}
		}

		if (v[1] == 0)
			return f;

		for (i = 1; i != 0; i = p[i]) {
			adj[p[i]][i] = 0;
			adj[i][p[i]] = 1;
		}
	}
}


int main()
{
	double gx[128], gy[128], hx[128], hy[128], d, dmax;
	int i, j, n, m, s, v;

	while (scanf("%d %d %d %d", &n, &m, &s, &v) == 4) {
		for (i = 0; i < n; i++)
			scanf("%lf %lf", &gx[i], &gy[i]);

		for (i = 0; i < m; i++)
			scanf("%lf %lf", &hx[i], &hy[i]);

		nvert = 2 + n + m;
		for (i = 0; i < nvert; i++)
			for (j = 0; j < nvert; j++)
				adj[i][j] = 0;

		for (i = 0; i < n; i++)
			adj[0][2 + i] = 1;

		for (i = 0; i < m; i++)
			adj[2 + n + i][1] = 1;

		dmax = v * v * s * s + 1e-12;
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++) {
				d = (gx[i] - hx[j]) * (gx[i] - hx[j]) +
				    (gy[i] - hy[j]) * (gy[i] - hy[j]);
				if (d <= dmax)
					adj[2 + i][2 + n + j] = 1;
			}
		}

		printf("%d\n", n - maxflow());
	}

	return 0;
}
