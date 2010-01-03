#include <stdio.h>
#include <string.h>
#include <ctype.h>

int dx[256], dy[256], map_dx[16][16], map_dy[16][16], map[16][16];
int nrows, ncols, st;

void solve()
{
	int i, j, k, y, x;

	for (i = 0; i < nrows; i++) {
		for (j = 0; j < ncols && (k = getchar()) != EOF;) {
			if (dx[k] != 0 || dy[k] != 0) {
				map_dx[i][j] = dx[k];
				map_dy[i][j++] = dy[k];
			}
		}
	}

	memset(map, 0, sizeof(map));

	for (x = st - 1, y = 0, k = 1;;) {
		if (x < 0 || x >= ncols || y < 0 || y >= nrows) {
			printf("%d step(s) to exit\n", k - 1);
			return;
		}

		if (map[y][x]) {
			printf("%d step(s) before a loop of %d step(s)\n",
				map[y][x] - 1, k - map[y][x]);
			return;
		}

		map[y][x] = k++;
		i = map_dx[y][x];
		y += map_dy[y][x];
		x += i;
	}
}

int main()
{
	memset(dx, 0, sizeof(dx));
	memset(dy, 0, sizeof(dy));

	dy['N'] = dy['n'] = -1;
	dy['S'] = dy['s'] = 1;
	dx['E'] = dx['e'] = 1;
	dx['W'] = dx['w'] = -1;

	while (scanf("%d %d %d", &nrows, &ncols, &st) == 3 && nrows > 0)
		solve();

	return 0;
}
