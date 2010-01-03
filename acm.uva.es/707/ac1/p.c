#include <stdio.h>

typedef unsigned char map_t[128][128];

map_t map[128];
int w, h;

int merge(map_t x, map_t y)
{
	static int r;
	int i, j, k;

	for (r = 0, i = 1; i <= h; i++) {
		for (j = 1; j <= w; j++) {
			if (x[i][j]) {
				k = y[i][j] | y[i-1][j] | y[i+1][j] | y[i][j-1] | y[i][j+1];
				r |= (x[i][j] ^ k);
				x[i][j] = k;
			}

			if (y[i][j]) {
				k = x[i][j] | x[i-1][j] | x[i+1][j] | x[i][j-1] | x[i][j+1];
				r |= (y[i][j] ^ k);
				y[i][j] = k;
			}
		}
	}

	return r;
}

int sum(map_t x)
{
	int i, j, s;

	for (s = 0, i = 1; i <= h; i++)
		for (j = 1; j <= w; j++)
			s += x[i][j];

	return s;
}

int main()
{
	static int x[2], y[2], z[128], c, n, s, t;
	int i, j, k;

	for (c = 1; scanf("%d %d %d %d", &w, &h, &t, &n) == 4 && w > 0; c++) {
		for (k = 1; k <= t; k++) {
			for (i = 1; i <= h; i++) {
				map[k][i][0] = map[k][i][w + 1] = 0;
				for (j = 1; j <= w; j++)
					map[k][i][j] = 1;
			}

			for (i = 0; i <= (w + 1); i++)
				map[k][0][i] = map[k][h + 1][i] = 0;
		}

		while (n-- > 0) {
			scanf("%d %d %d %d %d", &s, &x[0], &y[0], &x[1], &y[1]);
			for (i = y[0]; i <= y[1]; i++)
				for (j = x[0]; j <= x[1]; j++)
					map[s][i][j] = 0;
		}

		for (;;) {
			for (k = 0, i = 2; i <= t; i++) {
				if (merge(map[i - 1], map[i]) == 0) continue;

				if (sum(map[i - 1]) == 0 || sum(map[i]) == 0)
					break;

				k++;
			}

			if (i <= t || k == 0)
				break;
		}

		printf("Robbery #%d:\n", c);

/*for (k=1;k<=t;k++){printf("\n");for(i=1;i<=h;i++){for(j=1;j<=w;j++)putchar(map[k][i][j]+'0');putchar('\n');}}*/

		for (i = 1, k = 0; i <= t; i++) {
			z[i] = sum(map[i]);

			if (z[i] == 0)
				break;
			else if (z[i] == 1)
				k++;
		}

		if (i <= t) {
			printf("The robber has escaped.\n\n");
			continue;
		}

		if (k == 0) {
			printf("Nothing known.\n\n");
			continue;
		}

		for (k = 1; k <= t; k++) {
			if (z[k] != 1)
				continue;

			for (i = 1, j =0; i <= h; i++) {
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
