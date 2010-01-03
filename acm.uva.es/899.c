#include <stdio.h>
#include <string.h>

#define GET(p,c) (((p[(c) >> 5]) >> ((c) & 31)) & 1)

unsigned adj[128][128][4];
int color[128], src1, src2, dest, n;

int solve()
{
	static int dist[65536], queue[131072];
	int d, x, y, z, *head, *tail;

	memset(dist, 0, sizeof(dist));

	head = tail = queue;
	*tail++ = src1;
	*tail++ = src2;
	dist[(src1 << 7) | src2] = dist[(src2 << 7) | src1] = 1;

	while (head < tail) {
		x = *head++;
		y = *head++;
		d = dist[(x << 7) | y] + 1;

		for (z = 1; z <= n; z++) {
			if (z == y || !GET(adj[x][z], color[y]))
				continue;

			if (dist[(z << 7) | y] != 0)
				continue;

			if (z == dest)
				return (d - 1);

			dist[(z << 7) | y] = dist[(y << 7) | z] = d;
			*tail++ = z;
			*tail++ = y;
		}

		for (z = 1; z <= n; z++) {
			if (z == x || !GET(adj[y][z], color[x]))
				continue;

			if (dist[(z << 7) | x] != 0)
				continue;

			if (z == dest)
				return (d - 1);

			dist[(z << 7) | x] = dist[(x << 7) | z] = d;
			*tail++ = z;
			*tail++ = x;
		}
	}

	return 0;
}

int main()
{
	int i, j, m, x, y, z;

	while (scanf("%d %d %d %d %d", &n, &src1, &src2, &dest, &m) == 5 && n) {
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				adj[i][j][0] = adj[i][j][1] = adj[i][j][2] = adj[i][j][3] = 0;

		for (i = 1; i <= n; i++)
			scanf("%d", &color[i]);

		while (m-- > 0 && scanf("%d %d %d", &x, &y, &z) == 3)
			adj[x][y][z >> 5] |= 1U << (z & 31);

		printf("%d\n", solve());
	}

	return 0;
}
