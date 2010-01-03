#include <stdio.h>

static unsigned char map[102][128][128];
static int w, h, t;

void search_bot()
{
	register int i, j, k, m;

	for (m = 1; m < t; m++) {
		for (i = 1; i <= h; i++) {
			for (j = 1; j <= w; j++) {
				if (map[m + 1][i][j] == 0)
					continue;

				k = map[m][i][j] |
				    map[m][i][j - 1] | map[m][i][j + 1] |
				    map[m][i - 1][j] | map[m][i + 1][j];
				map[m + 1][i][j] &= k;
			}
		}
	}
}

void search_top()
{
	register int i, j, k, m;

	for (m = t; m > 1; m--) {
		for (i = 1; i <= h; i++) {
			for (j = 1; j <= w; j++) {
				if (map[m - 1][i][j] == 0)
					continue;

				k = map[m][i][j] |
				    map[m][i][j - 1] | map[m][i][j + 1] |
				    map[m][i - 1][j] | map[m][i + 1][j];
				map[m - 1][i][j] &= k;
			}
		}
	}
}

int main()
{
	static int a[128], x[2], y[2], r, n, s;
	register int i, j, k;

	for (r = 1; scanf("%d %d %d %d", &w, &h, &t, &n) == 4 && w > 0; r++) {
		for (k = 1; k <= t; k++) {
			for (i = 0; i <= w; i++)
				map[k][0][i] = map[k][h + 1][i] = 0;

			for (i = 0; i <= h; i++)
				map[k][i][0] = map[k][i][w + 1] = 0;

			for (i = 1; i <= h; i++)
				for (j = 1; j <= w; j++)
					map[k][i][j] = 1;
		}

		while (n-- > 0) {
			scanf("%d %d %d %d %d", &s, &x[0], &y[0], &x[1], &y[1]);

			for (i = y[0]; i <= y[1]; i++)
				for (j = x[0]; j <= x[1]; j++)
					map[s][i][j] = 0;
		}

		search_bot();
		search_top();

		for (n = 1; n <= t; n++) {
			for (k = 0, i = 1; i <= h; i++)
				for (j = 1; j <= w; j++)
					k += map[n][i][j];
			a[n] = k;
		}

		printf("Robbery #%d:\n", r);

		for (i = 1; i <= t; i++)
			if (a[i] == 0) break;

		if (i <= t) {
			printf("The robber has escaped.\n\n");
			continue;
		}

		for (i = 1; i <= t; i++)
			if (a[i] == 1) break;

		if (i > t) {
			printf("Nothing known.\n\n");
			continue;
		}

		for (k = 1; k <= t; k++) {
			if (a[k] != 1)
				continue;

			for (i = 1; i <= h; i++) {
				for (j = 1; j <= w; j++)
					if (map[k][i][j]) break;
				if (j <= w) break;
			}

			printf("Time step %d: The robber has been at %d,%d.\n",
			       k, j, i);
		}
		printf("\n");
	}

	return 0;
}
