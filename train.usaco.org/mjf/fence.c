/*
ID: mjf28791
PROG: fence
LANG: C
*/
#include <stdio.h>
#include <string.h>

int adj[512][512], deg[512], path[65536], len;

void rem(int u, int v)
{
	int i;

	for (i = 0; i < deg[u] && adj[u][i] != v; i++);

	for (; i < deg[u]; i++)
		adj[u][i] = adj[u][i + 1];
	deg[u]--;
}

void find(int s)
{
	int t;

	while (deg[s] > 0) {
		t = adj[s][deg[s] - 1];
		rem(s, t);
		rem(t, s);
		find(t);
	}

	path[len++] = s;
}

void add(int u, int v)
{
	int i;

	for (i = deg[u]++; i >= 0 && adj[u][i] < v; i--)
		adj[u][i + 1] = adj[u][i];
	adj[u][i + 1] = v;
}

int main()
{
	int m, u, v;

	freopen("fence.in", "r", stdin);
	freopen("fence.out", "w", stdout);

	memset(deg, 0, sizeof(deg));

	scanf("%d", &m);
	while (m-- >0 && scanf("%d %d", &u, &v) == 2) {
		add(u, v);
		add(v, u);
	}

	for (u = 1; u <= 500 && (deg[u] % 2) == 0; u++);

	if (u > 500)
		for (u = 1; u <= 500 && deg[u] == 0; u++);

	len = 0;
	find(u);

	while (len-- > 0)
		printf("%d\n", path[len]);

	return 0;
}
