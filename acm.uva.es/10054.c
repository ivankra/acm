#include <stdio.h>
#include <string.h>

int adj[64][64], deg[64], m;
int cyc[65536], top;

void find()
{
	int x, y, s;

	for (s = top, x = cyc[top - 1];;) {
 		for (y = 50; y >= 1 && adj[x][y] <= 0; y--);

		if (y <= 0)
			break;

		adj[x][y]--;
		adj[y][x]--;
		/* deg[x]--; deg[y]--; */

		cyc[top++] = y;
		x = y;
	}

	while (top > s) {
		printf("%d %d\n", cyc[top - 1], cyc[top - 2]);
		top--;

		find();
	}
}

int conn()
{
	static int v[64], s[64];
	int x, y, t;

	for (x = 1; x <= 50 && deg[x] == 0; x++);
	if (x > 50) return 1;

	memset(v, 0, sizeof(v));

	for (t = 1, s[0] = x, v[x] = 1; t > 0;)
		for (x = s[--t], y = 1; y <= 50; y++)
			if (adj[x][y] > 0 && v[y] == 0) v[s[t++] = y] = 1;

	for (x = 1; x <= 50; x++)
		if (deg[x] != 0 && v[x] == 0) return 0;

	return 1;
}

int solve()
{
	int i, j, x, y;

	memset(adj, 0, sizeof(adj));
	memset(deg, 0, sizeof(deg));

	scanf("%d", &m);

	for (i = 0; i < m && scanf("%d %d", &x, &y) == 2; i++) {
		adj[x][y]++;
		adj[y][x]++;
		deg[x]++;
		deg[y]++;
	}

	for (i = 1; i <= 50; i++)
		if (deg[i] & 1) return 1;

	if (!conn())
		return 1;

	for (i = 1; i <= 50 && deg[i] == 0; i++);

	cyc[0] = i;
	top = 1;

	find();

	return 0;
}

int main()
{
	int c, t;

	for (scanf("%d", &t), c = 1; c <= t; c++) {
		printf("%sCase #%d\n", (c == 1) ? "" : "\n", c);
		if (solve())
			printf("some beads may be lost\n");
	}

	return 0;
}
