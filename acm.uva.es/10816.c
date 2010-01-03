#include <stdio.h>

#define MAXN 128
#define MAXE 16384
#define INF 0x3FFFFFFF

int main()
{
	static int ix[MAXE], iy[MAXE], it[MAXE], id[MAXE], d[MAXN][MAXN];
	static int p[MAXN][MAXN], a, b, c, e, f, m, n, src, dest;
	register int i, j, k;

	while (scanf("%d %d %d %d", &n, &e, &src, &dest) == 4) {
		for (i = 0; i < e; i++) {
			scanf("%d %d %d . %d %d . %d",
			      &ix[i], &iy[i], &a, &b, &c, &f);
			it[i] = a * 10 + b;
			id[i] = c * 10 + f;
		}

		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++)
				d[i][j] = INF;
			d[i][i] = 0;
		}

		for (i = 0; i < e; i++) {
			a = ix[i];
			b = iy[i];
			if (it[i] < d[a][b])
				d[a][b] = d[b][a] = it[i];
		}

		for (k = 1; k <= n; k++) {
			for (i = 1; i <= n; i++) {
				if (i == k || d[i][k] == INF)
					continue;

				for (j = i + 1; j <= n; j++) {
					if (d[i][k] > d[k][j])
						a = d[i][k];
					else
						a = d[k][j];

					if (a < d[i][j])
						d[i][j] = d[j][i] = a;
				}
			}
		}

		m = d[src][dest];

		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++)
				d[i][j] = INF;
			d[i][i] = 0;
		}

		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				p[i][j] = j;

		for (i = 0; i < e; i++) {
			a = ix[i];
			b = iy[i];

			if (it[i] <= m && id[i] < d[a][b])
				d[a][b] = d[b][a] = id[i];
		}

		for (k = 1; k <= n; k++) {
			for (i = 1; i <= n; i++) {
				if (i == k || d[i][k] == INF)
					continue;

				for (j = 1; j <= n; j++) {
					a = d[i][k] + d[k][j];
					if (a >= d[i][j])
						continue;

					d[i][j] = d[j][i] = a;
					p[i][j] = p[i][k];
					p[j][i] = p[j][k];
				}
			}
		}

		for (i = src; i > 0; i = p[i][dest]) {
			if (i == dest) {
				printf("%d\n", i);
				break;
			}
			printf("%d ", i);
		}

		printf("%d.%d %d.%d\n",
		       d[src][dest] / 10, d[src][dest] % 10,
		       m / 10, m % 10);
	}

	return 0;
}
