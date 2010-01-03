#include <stdio.h>
#include <string.h>

int nrows, ncols, endx, endy;
int map[32][32], dist[32768], queue[32768], head, tail;
int dy[] = { -1, 0, 1, 0 }, dx[] = { 0, 1, 0, -1 };

int state(int y, int x, int d, int c)
{
	return (y << 10) | (x << 5) | (d << 3) | c;
}

void push(int s, int d)
{
	if (dist[s] == 0) {
		dist[s] = d;
		queue[tail++] = s;
	}
}

int solve()
{
	int i, j, k, y, x, d, c;

	memset(map, 1, sizeof(map));
	memset(dist, 0, sizeof(dist));

	for (i = 1; i <= nrows; i++) {
		for (j = 1; j <= ncols && (k = getchar()) != EOF;) {
			if (k == '.') {
				map[i][j++] = 0;
			} else if (k == '#') {
				map[i][j++] = 1;
			} else if (k == 'S') {
				queue[0] = state(i, j, 0, 0);
				map[i][j++] = 0;
			} else if (k == 'T') {
				endy = i;
				endx = j;
				map[i][j++] = 0;
			}
		}
	}

	dist[queue[0]] = 1;
	head = 0; tail = 1;

	while (head < tail) {
		k = queue[head++];

		y = k >> 10;
		x = (k >> 5) & 0x1F;
		d = (k >> 3) & 3;
		c = k & 7;

		for (i = -1; i <= 1; i += 2)
			push(state(y, x, (d + 4 + i) % 4, c), dist[k] + 1);

		y += dy[d];
		x += dx[d];

		if (map[y][x] == 0)
			push(state(y, x, d, (c + 1) % 5), dist[k] + 1);
	}

	for (i = 0, j = 0; i < 4; i++) {
		k = state(endy, endx, i, 0);
		if (dist[k] != 0 && (j == 0 || dist[k] < j))
			j = dist[k];
	}

	return (j - 1);
}

int main()
{
	int r, t;

	for (t = 1; scanf("%d %d", &nrows, &ncols) == 2 && nrows > 0; t++) {
		printf("%sCase #%d\n", (t == 1) ? "" : "\n", t);

		r = solve();

		if (r < 0)
			printf("destination not reachable\n");
		else
			printf("minimum time = %d sec\n", r);
	}

	return 0;
}
