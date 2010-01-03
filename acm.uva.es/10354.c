#include <stdio.h>

#define INF 0x1FFFFFFF

int adj[128][128], ban[128], n;

void dij(int d[], int s)
{
	int i, j, v[128];

	for (i = 1; i <= n; i++) { v[i] = ban[i]; d[i] = INF; }
	d[s] = (ban[s] ? INF : 0);

	for (;;) {
		for (i = 1; i <= n && v[i]; i++);
		for (j = i + 1; j <= n; j++) if (!v[j] && d[j] < d[i]) i = j;
		if (i > n || d[i] >= INF) break;

		for (v[i] = 1, j = 1; j <= n; j++)
			if ((d[i] + adj[i][j]) < d[j]) d[j] = d[i] + adj[i][j];
	}

	for (i = 1; i <= n; i++)
		if (ban[i]) d[i] = INF;
}

int main()
{
	static int d[128], e[128], m, u1, u2, v1, v2, x, y, z;
	int i, j;

	while (scanf("%d %d %d %d %d %d", &n, &m, &u1, &u2, &v1, &v2) == 6) {
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				adj[i][j] = INF;

		while (m-- > 0 && scanf("%d %d %d", &x, &y, &z) == 3)
			if (adj[x][y] > z) adj[x][y] = adj[y][x] = z;

		for (i = 1; i <= n; i++)
			ban[i] = 0;

		dij(d, u1);
		dij(e, u2);

		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				if (adj[i][j] < INF &&
				    d[i] + adj[i][j] + e[j] == d[u2])
					adj[i][j] = adj[j][i] = INF;

		for (i = 1; i <= n; i++)
			ban[i] = (d[i] + e[i] == d[u2]);

		dij(d, v1);
		printf((d[v2] >= INF) ? "MISSION IMPOSSIBLE.\n" : "%d\n", d[v2]);
	}

	return 0;
}
