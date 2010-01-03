#include <stdio.h>
#include <string.h>

struct { int x, y, t; } meet[65536];
struct { int y, t; } adj[32][128];
int adjn[32], n, m;

int search()
{
	static int v[32], dist[32], q[65536], head, tail;
	int i, k, x, y;

	memset(v, 0, sizeof(v));

	head = tail = 0;
	q[tail++] = 0;
	dist[0] = 0;

	while (head < tail) {
		x = q[head++];
		v[x] = 1;

		for (i = 0; i < adjn[x]; i++) {
			y = adj[x][i].y;

			if (adj[x][i].t < (dist[x] % 100))
				k = ((dist[x] / 100) + 1) * 100 + adj[x][i].t;
			else
				k = ((dist[x] / 100) + 0) * 100 + adj[x][i].t;

			if (v[y] == 0 || (dist[y] > k)) {
				v[y] = 1;
				dist[y] = k;
				q[tail++] = y;
			}
		}
	}

	for (k = 0, i = 1; i < n; i++)
		if (dist[i] > k) k = dist[i];

	return k;
}

int solve()
{
	static int cl[32][32];
	int i, j, k;

	memset(cl, 0, sizeof(cl));
	for (i = 0; i < m; i++)
		cl[meet[i].x][meet[i].y] = cl[meet[i].y][meet[i].x] = 1;

	for (i = 0; i < n; i++)
		cl[i][i] = 1;

	for (k = 0; k < n; k++)
		for (i = 0; i < n; i++)
			if (cl[i][k])
				for (j = 0; j < n; j++) cl[i][j] |= cl[k][j];

	for (i = 1; i < n; i++)
		if (cl[0][i] == 0) return -1;

	return search();
}

int main()
{
	int t, k, x, y, v, z;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &k) == 2;) {
		memset(adjn, 0, sizeof(adjn));

		for (m = 0; k-- > 0 && scanf("%d %d %d", &x, &y, &v) == 3;) {
			for (x--, y--; v-- > 0 && scanf("%d", &z) == 1;) {
				meet[m].x = x;
				meet[m].y = y;
				meet[m++].t = z;

				adj[x][adjn[x]].y = y;
				adj[x][adjn[x]++].t = z;

				adj[y][adjn[y]].y = x;
				adj[y][adjn[y]++].t = z;
			}
		}

		printf("%d\n", solve());
	}

	return 0;
}
