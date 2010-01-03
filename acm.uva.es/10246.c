#include <stdio.h>
#include <stdlib.h>

#define INF 0x3FFFFFFF

int adj[128][128], lab[128], labv[128], nlabv, n;
int adjlist[128][128], ans[128][128];
int dist[16384], loc[16384], heap[16384], heapn;

void up(int p)
{
	int d, t;

	for (d = dist[t = heap[p]]; p > 1 && dist[heap[p >> 1]] > d; p >>= 1)
		loc[heap[p] = heap[p >> 1]] = p;
	loc[heap[p] = t] = p;
}

void down(int p)
{
	int i, j, d;

	for (d = dist[heap[p]]; (j = (p << 1)) <= heapn; p = i) {
		i = (dist[heap[j]] < d) ? j : p;
		j++;
		if (j <= heapn && dist[heap[j]] < dist[heap[i]]) i = j;

		if (i == p) break;

		j = heap[p];
		loc[heap[p] = heap[i]] = p;
		loc[heap[i] = j] = i;
	}
}

void make(int s)
{
	int i, j, k, u, t;

	k = (n + 2) << 7;
	for (i = 0; i < k; i++)
		dist[i] = INF;

	for (i = 1; i <= n; i++)
		ans[s][i] = INF;

	for (heapn = 0, i = lab[s]; i < nlabv; i++) {
		dist[u = (s << 7) | i] = 0;
		heapn++;
		loc[heap[heapn] = u] = heapn;
	}

	while (heapn > 0) {
		u = heap[1];
		loc[heap[1] = heap[heapn--]] = 1;
		if (heapn > 1) down(1);

		t = u >> 7;
		j = dist[u] + labv[u & 0x7F];
		if (j < ans[s][t])
			ans[s][t] = ans[t][s] = j;

		for (i = 0; adjlist[t][i]; i++) {
			k = adjlist[t][i];
			j = u & 0x7F;
			if (lab[k] > j) j = lab[k];
			j |= k << 7;

			if (dist[j] <= (dist[u] + adj[t][k]))
				continue;

			if (dist[j] == INF) {
				heapn++;
				loc[heap[heapn] = j] = heapn;
			}

			dist[j] = dist[u] + adj[t][k];
			up(loc[j]);
		}
	}
}

int cmp(const void *p, const void *q)
{
	return *(int *)p - *(int *)q;
}

int lfind(int l)
{
	int a, b, c;

	for (a = 0, b = nlabv - 1; a <= b;)
		if (labv[c = (a + b) >> 1] < l)
			a = c + 1;
		else if (labv[c] > l)
			b = c - 1;
		else
			return c;

	return a;
}

int main()
{
	static int m, q, t, x, y, z;
	int i, j, k;

	for (t = 1; scanf("%d %d %d", &n, &m, &q) == 3 && n > 0; t++) {
		for (i = 1; i <= n; i++)
			scanf("%d", &lab[i]);

		for (i = 0; i < n; i++)
			labv[i] = lab[i+1];

		qsort(labv, n, sizeof(labv[0]), &cmp);
		for (nlabv = 1, i = 1; i < n; i++)
			if (labv[i - 1] != labv[i]) labv[nlabv++] = labv[i];

		for (i = 1; i <= n; i++)
			lab[i] = lfind(lab[i]);

		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++)
				adj[i][j] = INF;
			adj[i][i] = 0;
		}

		while (m-- > 0 && scanf("%d %d %d", &x, &y, &z) == 3)
			if (adj[x][y] > z)
				adj[x][y] = adj[y][x] = z;

		for (i = 1; i <= n; i++) {
			for (j = 1, k = 0; j <= n; j++)
				if (adj[i][j] < INF && i != j) adjlist[i][k++] = j;
			adjlist[i][k] = 0;
		}

		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++)
				ans[i][j] = -1;
			ans[i][i] = labv[lab[i]];
		}

		printf("%sCase #%d\n", (t == 1) ? "" : "\n", t);
		while (q-- > 0 && scanf("%d %d", &x, &y) == 2) {
			if (ans[x][y] < 0) make(x);
			printf("%d\n", (ans[x][y] == INF) ? -1 : ans[x][y]);
		}
	}

	return 0;
}
