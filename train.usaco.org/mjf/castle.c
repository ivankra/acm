/*
ID: mjf28791
PROG: castle
LANG: C
*/
#include <stdio.h>
#include <string.h>

#define WEST	1
#define NORTH	2
#define EAST	4
#define SOUTH	8

int wall[64][64], n, m;
int vis[64][64];

int dfs(int y, int x)
{
	static int s[65536];
	int t, r;

	r = 0;
	t = 0;
	s[t++] = y;
	s[t++] = x;
	vis[y][x] = 1;

	while (t > 0) {
		r++;
		x = s[--t];
		y = s[--t];

		if (!(wall[y][x] & NORTH) && vis[y - 1][x] == 0) {
			s[t++] = y - 1;
			s[t++] = x;
			vis[y - 1][x] = 1;
		}

		if (!(wall[y][x] & SOUTH) && vis[y + 1][x] == 0) {
			s[t++] = y + 1;
			s[t++] = x;
			vis[y + 1][x] = 1;
		}

		if (!(wall[y][x] & WEST) && vis[y][x - 1] == 0) {
			s[t++] = y;
			s[t++] = x - 1;
			vis[y][x - 1] = 1;
		}

		if (!(wall[y][x] & EAST) && vis[y][x + 1] == 0) {
			s[t++] = y;
			s[t++] = x + 1;
			vis[y][x + 1] = 1;
		}
	}

	return r;
}

int scan(int y, int x)
{
	memset(vis, 0, sizeof(vis));
	return dfs(y, x);
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int main()
{
	int i, j, k, x, y, z, w;

	freopen("castle.in", "r", stdin);
	freopen("castle.out", "w", stdout);

	scanf("%d %d", &m, &n);

	memset(wall, 0xFF, sizeof(wall));
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			scanf("%d", &wall[i][j]);

	memset(vis, 0, sizeof(vis));

	for (k = 0, x = 0, i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			if (vis[i][j])
				continue;

			k++;
			x = max(x, dfs(i, j));
		}
	}

	printf("%d\n%d\n", k, x);

	for (x = y = z = 0, w = '?', j = 1; j <= m; j++) {
		for (i = n; i >= 1; i--) {
			if (i >= 2 && wall[i][j] & NORTH) {
				wall[i][j] &= ~NORTH;
				wall[i - 1][j] &= ~SOUTH;

				k = scan(i, j);
				if (k > z)
					y = i, x = j, z = k, w = 'N';

				wall[i][j] |= NORTH;
				wall[i - 1][j] |= SOUTH;
			}

			if (j < m && wall[i][j] & EAST) {
				wall[i][j] &= ~EAST;
				wall[i][j + 1] &= ~WEST;

				k = scan(i, j);
				if (k > z)
					y = i, x = j, z = k, w = 'E';

				wall[i][j] |= EAST;
				wall[i][j + 1] |= WEST;
			}
		}
	}

	printf("%d\n%d %d %c\n", z, y, x, w);
	return 0;
}
