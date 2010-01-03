#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int x, y, z, r;
} edge_t;

edge_t edge[2048];
int deg[64], adj[64][64], m;

int connected(int a)
{
	static int v[64], s[64];
	int i, k, t;

	for (i = 1; i <= 44; i++) v[i] = 0;

	for (s[0] = a, v[a] = 1, t = 1; t > 0;)
		for (k = s[--t], i = 1; i <= 44; i++)
			if (adj[k][i] && !v[i]) v[s[t++] = i] = 1;

	for (i = 1; i <= 44; i++)
		if (deg[i] != 0 && v[i] == 0) return 0;

	return 1;
}

int compare(const void *p, const void *q)
{
	return (((edge_t *)p)->z - ((edge_t *)q)->z);
}

int min(int a, int b)
{
	return (a < b) ? a : b;
}

int solve()
{
	int i, k, v, left, start;

	start = min(edge[0].x, edge[0].y);

	for (i = 1; i <= 44; i++)
		if (deg[i] & 1) return 0;
	if (!connected(start)) return 0;

	qsort(edge, m, sizeof(edge[0]), &compare);

	for (left = m, v = start; left > 0; left--) {
		for (k = 0; k < m; k++) {
			if (edge[k].r || (edge[k].x != v && edge[k].y != v))
				continue;

			deg[edge[k].x]--;
			deg[edge[k].y]--;
			adj[edge[k].x][edge[k].y]--;
			adj[edge[k].y][edge[k].x]--;
			edge[k].r = 1;

			if (deg[v] == 0 || adj[edge[k].x][edge[k].y] > 0)
				break;

			if (connected(start))
				break;

			deg[edge[k].x]++;
			deg[edge[k].y]++;
			adj[edge[k].x][edge[k].y]++;
			adj[edge[k].y][edge[k].x]++;
			edge[k].r = 0;
		}

		printf((left > 1) ? "%d " : "%d\n\n", edge[k].z);
		v = (v == edge[k].x) ? edge[k].y : edge[k].x;
	}

	return 1;
}

int main()
{
	for (;;) {
		memset(deg, 0, sizeof(deg));
		memset(adj, 0, sizeof(adj));
		memset(edge, 0, sizeof(edge));

		for (m = 0; scanf("%d %d", &edge[m].x, &edge[m].y) == 2; m++) {
			if (edge[m].x == 0) break;
			scanf("%d", &edge[m].z);
			deg[edge[m].x]++;
			deg[edge[m].y]++;
			adj[edge[m].x][edge[m].y]++;
			adj[edge[m].y][edge[m].x]++;
		}

		if (m == 0)
			break;

		if (solve() == 0)
			printf("Round trip does not exist.\n\n");
	}

	return 0;
}
