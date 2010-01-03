/*
ID: mjf28791
PROG: maze1
LANG: C
*/
#include <stdio.h>
#include <string.h>

/* damn! grader's silly */
#define GETS(s) fgets(s, 0x7FFFFFFF, stdin)

#define NORTH	1
#define EAST	2
#define SOUTH	4
#define WEST	8

int map[128][128], dist[128][128], queue[65536], head, tail, w, h;

void add(int y, int x, int d)
{
	if (y < 1 || y > h || x < 1 || x > w || dist[y][x] <= d) return;
	queue[tail++] = y;
	queue[tail++] = x;
	dist[y][x] = d;
}

int main()
{
	char buf[1024], *s;
	int i, j, y, x;

	freopen("maze1.in", "r", stdin);
	freopen("maze1.out", "w", stdout);

	GETS(buf);
	sscanf(buf, "%d %d", &w, &h);

	memset(map, 0, sizeof(map));
	for (i = 1; i <= h; i++) {
		GETS(buf);
		for (s = buf + 1, j = 1; j <= w; j++, s += 2) {
			if (*s == '-') {
				map[i][j] |= NORTH;
				map[i - 1][j] |= SOUTH;
			}
		}

		GETS(buf);
		for (s = buf, j = 1; j <= (w + 1); j++, s += 2) {
			if (*s == '|') {
				map[i][j] |= WEST;
				map[i][j - 1] |= EAST;
			}
		}
	}

	GETS(buf);
	for (s = buf + 1, j = 1; j <= w; j++, s += 2)
		if (*s == '-') map[i - 1][j] |= SOUTH;

	for (i = 1; i <= h; i++)
		for (j = 1; j <= w; j++)
			dist[i][j] = 0x7FFFFFFF;

	head = tail = 0;

	for (i = 1; i <= w; i++) {
		if ((map[1][i] & NORTH) == 0) add(1, i, 1);
		if ((map[h][i] & SOUTH) == 0) add(h, i, 1);
	}

	for (i = 1; i <= h; i++) {
		if ((map[i][1] & WEST) == 0) add(i, 1, 1);
		if ((map[i][w] & EAST) == 0) add(i, w, 1);
	}

	while (head < tail) {
		y = queue[head++];
		x = queue[head++];

		if ((map[y][x] & NORTH) == 0)
			add(y - 1, x, dist[y][x] + 1);

		if ((map[y][x] & SOUTH) == 0)
			add(y + 1, x, dist[y][x] + 1);

		if ((map[y][x] & EAST) == 0)
			add(y, x + 1, dist[y][x] + 1);

		if ((map[y][x] & WEST) == 0)
			add(y, x - 1, dist[y][x] + 1);
	}


	for (x = 0, i = 1; i <= h; i++)
		for (j = 1; j <= w; j++)
			if (dist[i][j] > x) x = dist[i][j];

	printf("%d\n", x);
	return 0;
}
