#include <stdio.h>
#include <string.h>

int adj[128][128], n;
int src1, src2, dest;

int enc(int x, int y)
{
	return (x < y) ? ((x - 1) * n + y - 1) : ((y - 1) * n + x - 1);
}

void dec(int s, int *x, int *y)
{
	(*x) = (s / n) + 1;
	(*y) = (s % n) + 1;
}

int solve()
{
	static int d[16384], q[16384];
	int h, t, x, y, z;

	h = t = 0;
	memset(d, 0, sizeof(d));
	d[q[t++] = enc(src1, src2)] = 1;

	for (; h < t; h++) {
		dec(q[h], &x, &y);
		if (x == dest || y == dest)
			return (d[q[h]] - 1);

		if (adj[x][y] > 0) {
			z = enc(adj[x][y], y);
			if (d[z] == 0) d[q[t++] = z] = d[q[h]] + 1;
		}

		if (adj[y][x] > 0) {
			z = enc(x, adj[y][x]);
			if (d[z] == 0) d[q[t++] = z] = d[q[h]] + 1;
		}
	}

	return -1;
}

int main()
{
	int i, j, t;

	for (t = 1; scanf("%d", &n) == 1 && n >= 3; t++) {
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				scanf("%d", &adj[i][j]);

		scanf("%d %d %d", &src1, &src2, &dest);

		printf("Game #%d\n", t);
		if ((i = solve()) < 0)
			printf("Destination is Not Reachable !\n\n");
		else
			printf("Minimum Number of Moves = %d\n\n", i);
	}

	return 0;
}
