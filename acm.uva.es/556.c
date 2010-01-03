#include <stdio.h>

int a[256][256], c[256][256], r[8], h, w;
int dx[] = { 1, 0, -1, 0 }, dy[] = { 0, -1, 0, 1 };

int main()
{
	int i, j, k, x, y, d;

	while (scanf("%d %d", &h, &w) == 2 && h > 0) {
		for (i = 1; i <= h; i++)
			for (j = 1; j <= w && (k = getchar()) != EOF;)
				if (k == '0' || k == '1') a[i][j++] = k - '0';

		for (i = 0; i <= (w + 1); i++)
			a[0][i] = a[h + 1][i] = 1;

		for (i = 0; i <= (h + 1); i++)
			a[i][0] = a[i][w + 1] = 1;

		for (i = 1; i <= h; i++)
			for (j = 1; j <= w; j++)
				c[i][j] = 0;

		for (y = h, x = 1, d = 0;;) {
			c[y][x]++;

			if (!a[y + dy[(d + 3) & 3]][x + dx[(d + 3) & 3]])
				d = (d + 3) & 3;

			while (a[y + dy[d]][x + dx[d]]) d = (d + 1) & 3;

			y += dy[d];
			x += dx[d];

			if (y == h && x == 1) break;
		}

		for (i = 0; i <= 4; i++)
			r[i] = 0;

		for (i = 1; i <= h; i++)
			for (j = 1; j <= w; j++)
				if (!a[i][j] && c[i][j] <= 4) r[c[i][j]]++;

		for (i = 0; i < 5; i++)
			printf((i < 4) ? "%3d" : "%3d\n", r[i]);
	}

	return 0;
}
