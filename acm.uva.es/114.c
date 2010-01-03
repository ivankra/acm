#include <stdio.h>

int map[64][64], cost[64][64], val[64][64];
int m, n, x, y, d, t;
int dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };

int solve()
{
	int r;

	for (r = 0; t > 0;) {
		if (map[x + dx[d]][y + dy[d]] == 0) {
			x += dx[d];
			y += dy[d];
			t--;
		} else if (map[x + dx[d]][y + dy[d]] == 'w') {
			t -= 1 + cost[x + dx[d]][y + dy[d]];
			d = (d + 3) % 4;
		} else {
			if (t <= 1) break;
			t -= 1 + cost[x + dx[d]][y + dy[d]];
			r += val[x + dx[d]][y + dy[d]];
			d = (d + 3) % 4;
		}
	}

	return r;
}

int main()
{
	int i, j, c, p, v;

	scanf("%d %d %d %d", &m, &n, &c, &p);

	for (i = 0; i <= (m + 1); i++) {
		for (j = 0; j <= (n + 1); j++) {
			map[i][j] = 'w';
			cost[i][j] = c;
			val[i][j] = 0;
		}
	}

	for (i = 2; i < m; i++)
		for (j = 2; j < n; j++)
			map[i][j] = 0;

	while (p-- > 0 && scanf("%d %d %d %d", &x, &y, &v, &c) == 4) {
		map[x][y] = 'b';
		cost[x][y] = c;
		val[x][y] = v;
	}

	for (v = 0; scanf("%d %d %d %d", &x, &y, &d, &t) == 4;) {
		printf("%d\n", c = solve());
		v += c;
	}

	printf("%d\n", v);
	return 0;
}
