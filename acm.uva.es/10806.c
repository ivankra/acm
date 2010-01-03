#include <stdio.h>

#define INF 0x1fffffff

int main()
{
	static int a[128][128], d[128][128], s[128][128], m, n, x, y, z;
	int i, j, k;

	while (scanf("%d %d", &n, &m) == 2 && n > 0) {
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++)
				a[i][j] = INF;
			a[i][i] = 0;
		}

		while (m-- > 0 && scanf("%d %d %d", &x, &y, &z) == 3)
			a[x][y] = a[y][x] = z;

		for (x = z = 0; x < 2; x++) {
			for (i = 1; i <= n; i++) {
				for (j = 1; j <= n; j++) {
					d[i][j] = a[i][j];
					s[i][j] = j;
				}
			}

			for (k = 1; k <= n; k++)
				for (i = 1; i <= n; i++)
					for (j = 1; j <= n; j++)
						if ((d[i][k] + d[k][j]) < d[i][j])
							d[i][j] = d[i][k] + d[k][j],
							s[i][j] = s[i][k];

			if (d[1][n] >= INF) {
				z = INF;
				break;
			}

			z += d[1][n];

			if (x < 1) {
				for (i = 1; i != n; i = s[i][n]) {
					j = s[i][n];
					a[i][j] = INF;
					a[j][i] = -d[j][i];
				}
			}
		}

		printf((z >= INF) ? "Back to jail\n" : "%d\n", z);
	}

	return 0;
}
