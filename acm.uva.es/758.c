#include <stdio.h>
#include <string.h>

int cluster[16][16], count[16][16], score, balls;
char color[16][16];

void shift()
{
	int r, c, k, m;

	for (c = 0, m = 14; c <= m;) {
		for (k = 0, r = 0; r < 10; r++)
			if (color[r][c] != 0)
				color[k++][c] = color[r][c];

		for (r = k; r < 10; r++)
			color[r][c] = 0;

		if (k > 0) {
			c++;
			continue;
		}

		for (k = c + 1; k <= m; k++)
			for (r = 0; r < 10; r++)
				color[r][k - 1] = color[r][k];

		for (r = 0; r < 10; r++)
			color[r][m] = 0;

		m--;
	}
}

void dfs(int y, int x, int c)
{
	static int s[8192];
	int i, j, k;

	i = 0;
	s[i++] = y;
	s[i++] = x;
	cluster[y][x] = c;

	for (k = 1; i > 0;) {
		x = s[--i];
		y = s[--i];

#define CHECK(Y,X) \
	if (0 <= (Y) && (Y) < 10 && 0 <= (X) && (X) < 15 && \
	    color[Y][X] == color[y][x] && cluster[Y][X] != c) { \
		cluster[Y][X] = c; \
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

	for (i = 0; i < 10; i++)
		for (j = 0; j < 15; j++)
			if (cluster[i][j] == c)
				count[i][j] = k;
}

void solve()
{
	int i, j, k, m;

	for (m = 1;; m++) {
		memset(cluster, 0, sizeof(cluster));
		memset(count, 0, sizeof(count));

		for (i = k = 0; i < 10; i++)
			for (j = 0; j < 15; j++)
				if (color[i][j] && cluster[i][j] == 0)
					dfs(i, j, ++k);

		for (i = k = 0; i < 10; i++)
			for (j = 0; j < 15; j++)
				if (count[i][j] > k)
					k = count[i][j];

		if (k <= 1)
			return;

		for (j = 0; j < 15; j++) {
			for (i = 0; i < 10; i++)
				if (count[i][j] == k) break;
			if (i < 10) break;
		}

		printf("Move %d at (%d,%d): removed %d balls of color %c, got %d points.\n",
			m, i + 1, j + 1, k, color[i][j], (k - 2) * (k - 2));

		balls -= k;
		score += (k - 2) * (k - 2);

		for (k = cluster[i][j], i = 0; i < 10; i++)
			for (j = 0; j < 15; j++)
				if (cluster[i][j] == k)
					color[i][j] = 0;

		shift();
	}
}

int main()
{
	int i, c, t;

	for (scanf("%d", &t), c = 1; c <= t; c++) {
		if (c != 1) printf("\n");

		printf("Game %d:\n\n", c);

		for (i = 9; i >= 0; i--)
			scanf(" %[A-Z]", color[i]);

		balls = 150;
		score = 0;

		solve();

		if (balls == 0)
			score += 1000;

		printf("Final score: %d, with %d balls remaining.\n", score, balls);
	}

	return 0;
}
