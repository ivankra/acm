#include <stdio.h>
#include <string.h>
#include <assert.h>

#define INF 0x0FFFFFFF

int src[16][16], dst[16][16], dir[16][16], into[16][16], height, width, best, res;
int dx[] = { 0, 1, -1, 0, 0 }, dy[] = { 0, 0, 0, 1, -1 }, opposite[8][8];

int min(int x, int y) { return (x < y) ? x : y; }

void check()
{
	int i, j;

	for (i = 1; i <= height; i++)
		for (j = 1; j <= width; j++)
			if (dst[i][j] == '.') {
				if (into[i][j] != 0) return;
			} else {
				if (into[i][j] != 1) return;
			}

	if (res < best) best = res;
}

void backtr(int row, int col)
{
	int r, c;

	if (res >= best) return;

	for (;;) {
		if (col > width) {
/*			if (row > 1) {
				for (c = 1; c <= width; c++)
					if (dst[row-1][c] != '.' && into[row-1][c] != 1) return;
			}
*/

			col = 1;
			row++;

			if (row > height) {
				check();
				return;
			}

			continue;
		}

		if (src[row][col] != '.') break;
		col++;
	}

	assert(1 <= row && row <= height);
	assert(1 <= col && col <= width);
	assert(src[row][col] == 'X' || src[row][col] == 'O');

	for (dir[row][col] = 0; dir[row][col] < 5; dir[row][col]++) {
		r = row + dy[dir[row][col]];
		c = col + dx[dir[row][col]];
		if (dst[r][c] != src[row][col] || into[r][c] != 0) continue;
		if (dir[r][c] >= 0 && opposite[dir[r][c]][dir[row][col]]) res++;
		into[r][c] = 1;
		backtr(row, col+1);
		into[r][c] = 0;
		if (dir[r][c] >= 0 && opposite[dir[r][c]][dir[row][col]]) res--;
	}

	dir[row][col] = -1;
}

int main()
{
	int i, j, c, t;

	memset(opposite, 0, sizeof(opposite));
	for (i = 1; i < 5; i++)
		for (j = 1; j < 5; j++)
			opposite[i][j] = ((dx[i] == -dx[j]) && (dy[i] == -dy[j]));

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &width, &height) == 2;) {
		assert(1 <= width && width <= 8 && 1 <= height && height <= 8);

		memset(src, 0, sizeof(src));
		memset(dst, 0, sizeof(dst));

		for (i = 1; i <= height; i++) {
			for (j = 1; j <= width && (c = getchar()) != EOF;)
				if (strchr("XO.", c) != NULL) src[i][j++] = c;
			for (j = 1; j <= width && (c = getchar()) != EOF;)
				if (strchr("XO.", c) != NULL) dst[i][j++] = c;
		}

		best = INF;
		res = 0;

		for (i = 0; i < 16; i++)
			for (j = 0; j < 16; j++)
				dir[i][j] = -1;
		memset(into, 0, sizeof(into));
		backtr(1, 1);

		printf("%d\n", (best < INF) ? best : -1);
	}

	return 0;
}
