#include <stdio.h>

int main()
{
	static int d[16][16], s[16][16], m, n, x, y, t;
	int i, j, k;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				d[i][j] = 0x3FFFFFFF;

		for (i = 1; i <= n; i++)
			for (d[i][i] = 0, j = 1; j <= n; j++)
				s[i][j] = j;

		for (i = 1; i <= n && scanf("%d", &m) == 1; i++)
			while (m-- > 0 && scanf("%d %d", &x, &y) == 2)
				if (i != x) d[i][x] = y;

		for (k = 1; k <= n; k++)
			for (i = 1; i <= n; i++)
				for (j = 1; j <= n; j++)
					if ((d[i][k] + d[k][j]) < d[i][j]) {
						d[i][j] = d[i][k] + d[k][j];
						s[i][j] = s[i][k];
					}

		scanf("%d %d", &x, &y);

		printf("Case %d: Path =", t);
		for (k = x;; k = s[k][y]) {
			printf(" %d", k);
			if (k == y) break;
		}

		printf("; %d second delay\n", d[x][y]);
	}

	return 0;
}

