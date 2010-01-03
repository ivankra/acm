#include <stdio.h>
#include <string.h>

int color[16][64], nrows, ncols;

void shift()
{
	int r, c, k, m;

	for (c = 0, m = ncols - 1; c <= m;) {
		for (k = 0, r = 0; r < nrows; r++)
			if (color[r][c] >= 0)
				color[k++][c] = color[r][c];

		for (r = k; r < nrows; r++)
			color[r][c] = -1;

		if (k > 0) {
			c++;
			continue;
		}

		for (k = c + 1; k <= m; k++)
			for (r = 0; r < nrows; r++)
				color[r][k - 1] = color[r][k];

		for (r = 0; r < nrows; r++)
			color[r][m] = -1;

		m--;
	}
}

int dfs(int y, int x)
{
	static int s[8192];
	int i, k, c;

	c = color[y][x];

	i = 0;
	if (y > 0 && color[y - 1][x] == c) i++;
	if ((y + 1) < nrows && color[y + 1][x] == c) i++;
	if (x > 0 && color[y][x - 1] == c) i++;
	if ((x + 1) < ncols && color[y][x + 1] == c) i++;

	if (i <= 0)
		return 1;

	i = 0;
	s[i++] = y;
	s[i++] = x;
	color[y][x] = -1;

	for (k = 1; i > 0;) {
		x = s[--i];
		y = s[--i];

#define CHECK(Y,X) \
	if (0 <= (Y) && (Y) < nrows && 0 <= (X) && (X) < ncols && \
	    color[Y][X] == c) { \
		color[Y][X] = -1; \
		s[i++] = Y; \
		s[i++] = X; \
		k++; \
	}

	CHECK(y - 1, x);
	CHECK(y + 1, x);
	CHECK(y, x - 1);
	CHECK(y, x + 1);

#undef CHECK

	}

	return 0;
}

int main()
{
	int i, j, c, x, y;

	for (c = 1; scanf("%d %d", &nrows, &ncols) == 2 && nrows != 0 && ncols != 0; c++) {
		printf("Grid %d.\n", c);

		for (i = 0; i < nrows; i++)
			for (j = 0; j < ncols; j++)
				scanf("%d", &color[i][j]);

		while (scanf("%d %d", &y, &x) == 2 && (y | x) != 0) {
			y--;
			x--;

			if (y < 0 || y >= nrows || x < 0 || x > ncols)
				continue;

			if (color[y][x] < 0)
				continue;

			if (dfs(y, x) == 0)
				shift();
		}

		for (i = 0; i < nrows; i++) {
			for (j = 0; j < ncols; j++)
				if (color[i][j] >= 0) break;
			if (j < ncols) break;
		}

		if (i >= nrows) {
			printf("    Game Won\n");
			continue;
		}

		for (i = nrows - 1; i >= 0; i--) {
			printf("    ");
			for (j = 0; j < ncols; j++)
				if (color[i][j] < 0)
					printf("  ");
				else
					printf("%d ", color[i][j]);
			printf("\n");
		}

		printf("\n");
	}

	return 0;
}
