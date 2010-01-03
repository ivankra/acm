#include <stdio.h>
#include <string.h>

int main()
{
	static int d[128][128], n, s, a, b, t;
	register int i, j, k;

	for (t = 1; scanf("%d %d", &n, &s) == 2 && n > 0; t++) {
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				d[i][j] = -1;

		while (scanf("%d %d", &a, &b) == 2 && (a | b) != 0)
			d[a][b] = 1;

		for (k = 1; k <= n; k++) {
			for (i = 1; i <= n; i++) {
				if (d[i][k] < 0)
					continue;

				for (j = 1; j <= n; j++) {
					if (d[k][j] < 0)
						continue;

					if ((d[i][k] + d[k][j]) <= d[i][j])
						continue;

					d[i][j] = d[i][k] + d[k][j];
				}
			}
		}

		for (k = 1, i = 2; i <= n; i++)
			if (d[s][i] > d[s][k]) k = i;

		printf("Case %d: The longest path from %d has length %d, "
		       "finishing at %d.\n\n",
		       t, s, d[s][k], k);
	}

	return 0;
}
