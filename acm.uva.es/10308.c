#include <stdio.h>
#include <string.h>

typedef struct {
	int x, y, z, r;
	int next;
} edge_t;

int adj[16384], n, last;
edge_t edge[65536];

void add(int x, int y, int z)
{
	int t;

	for (t = adj[x]; t != 0; t = edge[t].next)
		if (edge[t].y == y) return;

	t = ++last;
	edge[t].x = x;
	edge[t].y = y;
	edge[t].z = z;
	edge[t].r = -1;
	edge[t].next = adj[x];
	adj[x] = t;
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int ecost(int e)
{
	int r, t;

	if (edge[e].r >= 0)
		return edge[e].r;

	for (r = 0, t = adj[edge[e].y]; t != 0; t = edge[t].next)
		if (edge[t].y != edge[e].x) r = max(r, ecost(t));

	return (edge[e].r = r + edge[e].z);
}

int cost(int x)
{
	int t, m, r;

	for (t = adj[x], r = 0; t != 0; t = edge[t].next)
		r = max(r, ecost(t));

	return r;
}

int main()
{
	static char s[1024];
	int i, x, y, z;

	for (;;) {
		memset(adj, 0, sizeof(adj));

		for (last = i = 0; gets(s);) {
			i++;
			if (sscanf(s, "%d %d %d", &x, &y, &z) != 3) break;

			add(x, y, z);
			add(y, x, z);

		}

		if (i == 0)
			break;

		for (z = 0, x = 1; x <= 10000; x++)
			if (adj[x] != 0) z = max(z, cost(x));

		printf("%d\n", z);
	}

	return 0;
}
