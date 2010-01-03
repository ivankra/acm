#include <stdio.h>
#include <string.h>

static int d[16][16], tab[131072], n;

static int mincost(int v)
{
	int r, x, y, z;

	if (tab[v] != 0 || v == 0)
		return tab[v];

	for (x = 1; ((v >> x) & 1) == 0; x++);

	for (y = x + 1, r = 0x3FFFFFFF; y <= n; y++) {
		if ((v >> y) & 1) {
			z = d[x][y] + mincost(v ^ (1 << x) ^ (1 << y));
			if (z < r) r = z;
		}
	}

	return (tab[v] = r);
}

int main()
{
	static int m, r, v, x, y, z;
	int i, j, k;

	while (scanf("%d %d", &n, &m) == 2 && n > 0) {
		for (r = v = 0, i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				d[i][j] = 0x3FFFFFFF;

		while (m-- > 0 && scanf("%d %d %d", &x, &y, &z) == 3) {
			r += z;
			v ^= (1 << x) ^ (1 << y);

			if (d[x][y] > z)
				d[x][y] = d[y][x] = z;
		}

		for (k = 1; k <= n; k++)
			for (i = 1; i <= n; i++)
				for (j = i + 1; j <= n; j++)
					if ((d[i][k] + d[k][j]) < d[i][j])
						d[i][j] = d[j][i] = d[i][k] + d[k][j];

		memset(tab, 0, (1 << (n + 1)) * sizeof(int));
		r += mincost(v);

		printf("%d\n", r);
	}

	return 0;
}
