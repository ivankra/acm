#include <stdio.h>

#define INF 0x3FFFFFFF

int solve()
{
	static int d[128][128], n, m, x, y, z;
	int i, j, k;

	scanf("%d %d", &n, &m);

	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++)
			d[i][j] = INF;
		d[i][i] = 0;
	}

	while (m-- > 0 && scanf("%d %d %d", &x, &y, &z) == 3)
		if (d[x][y] > z) d[x][y] = d[y][x] = z;

	for (k = 1; k <= n; k++) {
		for (i = 1; i <= n; i++) {
			if (d[i][k] == INF) continue;
			for (j = i + 1; j <= n; j++)
				if ((d[i][k] + d[k][j]) < d[i][j])
					d[i][j] = d[j][i] = d[i][k] + d[k][j];
		}
	}

	for (z = INF, k = 1; k <= n; k++) {
		for (i = 2; i <= 5; i++)
			if (d[k][i] != d[k][1]) break;
		if (i <= 5) continue;

		for (j = d[k][1], i = 2; i <= n; i++)
			if (d[k][i] > j) j = d[k][i];

		if (j < z)
			z = j;
	}

	return (z == INF) ? -1 : z;
}

int main()
{
	int c, t;

	for (scanf("%d", &t), c = 1; c <= t; c++)
		printf("Map %d: %d\n", c, solve());

	return 0;
}
