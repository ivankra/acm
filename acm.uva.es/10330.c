#include <stdio.h>

#define INF	0x7fffffff
#define MAXM	131072

int adj[256], cap[MAXM], back[MAXM], ref[MAXM], next[MAXM], nvert, adjcnt;
int vin[256], vout[256], source, sink;

int find()
{
	static int p[256], q[256];
	int i, j, k;

	for (i = 0; i < nvert; i++)
		p[i] = 0;

	for (p[q[0] = source] = -1, j = 0, k = 1; j < k && p[sink] == 0;)
		for (i = adj[q[j++]]; i != 0; i = next[i])
			if (cap[i] > 0 && p[ref[i]] == 0)
				p[q[k++] = ref[i]] = i;

	if (p[sink] == 0)
		return 0;

	for (i = sink, k = INF; i != source; i = ref[back[p[i]]])
		if (cap[p[i]] < k) k = cap[p[i]];

	if (k == INF)
		return 0;

	for (i = sink; i != source; i = ref[back[p[i]]]) {
		if (cap[p[i]] < INF) cap[p[i]] -= k;
		if (cap[back[p[i]]] < INF) cap[back[p[i]]] += k;
	}

	return k;
}

void add(int u, int v, int c)
{
	int i, j;

	i = ++adjcnt;
	j = ++adjcnt;

	ref[i] = v;
	cap[i] = c;
	next[i] = adj[u];
	adj[u] = i;
	back[i] = j;

	ref[j] = u;
	cap[j] = 0;
	next[j] = adj[v];
	adj[v] = j;
	back[j] = i;
}

int main()
{
	int i, n, m, x, y, z;

	while (scanf("%d", &n) == 1) {
		source = 0;
		sink = 1;
		for (nvert = 2, i = 1; i <= n; i++) {
			vin[i] = nvert++;
			vout[i] = nvert++;
		}

		for (adjcnt = 0, i = 0; i < nvert; i++)
			adj[i] = 0;

		for (i = 1; i <= n && scanf("%d", &z) == 1; i++)
			add(vin[i], vout[i], z);

		for (scanf("%d", &m); m-- > 0 && scanf("%d %d %d", &x, &y, &z) == 3;)
			add(vout[x], vin[y], z);

		scanf("%d %d", &n, &m);

		while (n-- && scanf("%d", &x) == 1)
			add(source, vin[x], INF);

		while (m-- && scanf("%d", &x) == 1)
			add(vout[x], sink, INF);

		for (z = 0; (x = find()) > 0; z += x);
		printf("%d\n", z);
	}

	return 0;
}
