#include <stdio.h>

/* implements O(n^3) algorithm */

int main()
{
	static int m, n, a[128][128], c[128][128], d[128], r1, r2, x;
	register int i, j, s;

	while (scanf("%d%d", &m, &n) == 2 && (m | n) != 0) {
		for (i = 1; i <= m; i++)
			for (j = 1; j <= n; j++)
				scanf("%d", &a[i][j]);

		for (i = 0; i <= n; i++)
			c[0][i] = 0;

		for (i = 1; i <= m; i++) {
			for (c[i][0] = 0, j = 1, s = 0; j <= n; j++) {
				s += a[i][j];
				c[i][j] = c[i - 1][j] + s;
			}
		}

		for (r1 = 1, x = 0; r1 <= m; r1++) {
			for (r2 = r1; r2 <= m; r2++) {
				for (i = 1; i <= n; i++)
					d[i] = c[r2][i] - c[r1 - 1][i];

				for (s = 0, j = 0, i = 0; i < n; i++) {
					if (d[i] == d[i + 1]) {
						j++;
					} else {
						if (j > s) s = j;
						j = 0;
					}
				}
				if (j > s) s = j;

				s *= (r2 - r1 + 1);
				if (s > x) x = s;
			}
		}

		printf("%d\n", x);
	}

	return 0;
}
