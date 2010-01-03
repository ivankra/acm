#include <stdio.h>
#include <string.h>

int dist[64][64][4], qx[16384], qy[16384], qm[16384], head, tail;
int map[64][64], stx, sty, endx, endy, n;

void push(int x, int y, int m, int d)
{
	if (x < 1 || x > n || y < 1 || y > n || map[x][y] || dist[x][y][m])
		return;

	dist[x][y][m] = d;
	qx[tail] = x;
	qy[tail] = y;
	qm[tail] = m;
	tail++;
}


int solve()
{
	int x, y, m, d;

	memset(dist, 0, sizeof(dist));
	head = tail = 0;
	push(stx, sty, 0, 1);
	push(stx, sty, 1, 1);
	push(stx, sty, 2, 1);

	while (head < tail) {
		x = qx[head];
		y = qy[head];
		m = qm[head++];
		d = dist[x][y][m];

		if (x == endx && y == endy)
			return (d - 1);

		if (m != 0) {
			push(x + 2, y + 1, 0, d + 1);
			push(x + 2, y - 1, 0, d + 1);
			push(x - 2, y + 1, 0, d + 1);
			push(x - 2, y - 1, 0, d + 1);
			push(x + 1, y + 2, 0, d + 1);
			push(x + 1, y - 2, 0, d + 1);
			push(x - 1, y + 2, 0, d + 1);
			push(x - 1, y - 2, 0, d + 1);
		}

		if (m != 1) {
			push(x + 2, y + 2, 1, d + 1);
			push(x + 2, y - 2, 1, d + 1);
			push(x - 2, y + 2, 1, d + 1);
			push(x - 2, y - 2, 1, d + 1);
		}

		if (m != 2) {
			push(n - x + 1, y, 2, d + 1);
			push(x, n - y + 1, 2, d + 1);
		}
	}

	return -1;
}

int main()
{
	int x, y;

	while (scanf("%d", &n) == 1 && n > 0) {
		scanf("%d %d %d %d", &stx, &sty, &endx, &endy);

		n *= 2;
		memset(map, 0, sizeof(map));

		while (scanf("%d %d", &x, &y) == 2 && (x | y) != 0)
			map[x][y] = 1;

		if ((x = solve()) < 0)
			printf("Solution doesn't exist\n");
		else
			printf("Result : %d\n", x);
	}

	return 0;
}
