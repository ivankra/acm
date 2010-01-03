#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define INF  0x1fffffff
#define MAXN 2048
#define MAXM (256*1024)

int adjy[MAXN][MAXN], adjc[MAXN][MAXN], deg[MAXN], ex[MAXM], ey[MAXM], ez[MAXM];
int result[MAXN], ds[MAXN], dt[MAXN], av[MAXN], n, m, s, t;

int ax[MAXN], ay[MAXN], an;

void add(int low, int up)
{
	int a, b, i;

	if (low > up) return;

	for (a = 0, b = an; a < b;)
		if (ax[i = (a + b) >> 1] < low) a = i + 1; else b = i;
	i = a;

	while (ax[i] < low) i++;
	while (ax[i] <= up) ay[i++]++;
}

int bget(int r[], int n, int x)
{
	int a, b, c;
	for (a = 0, b = n - 1; a <= b;)
		if (r[c = (a + b) >> 1] < x)
			a = c + 1;
		else if (r[c] > x)
			b = c - 1;
		else
			return c;
	assert(0 == 1);
	return -1;
}

int cmp(const void *p, const void *q)
{
	return *(int *)p - *(int *)q;
}

void dijkstra(int dist[], int src)
{
	static int v[MAXN];
	int i, j;

	for (i = 1; i <= n; i++) dist[i] = INF;
	dist[src] = 0;

	for (i = 1; i <= n; i++) v[i] = 0;

	for (;;) {
		for (i = 1; i <= n && v[i]; i++);
		if (i > n) break;

		for (j = i + 1; j <= n; j++)
			if (v[j] == 0 && dist[j] < dist[i]) i = j;

		if (dist[i] == INF) break;

		for (v[i] = 1, j = 0; j < deg[i]; j++)
			if (dist[adjy[i][j]] > (dist[i] + adjc[i][j]))
				dist[adjy[i][j]] = dist[i] + adjc[i][j];
	}
}

int main()
{
	int i, j;

	scanf("%d %d %d %d", &n, &s, &t, &m);
	assert(1 <= n && n <= MAXN);

	memset(deg, 0, sizeof(deg));

	for (i = 0; i < m; i++) {
		scanf("%d %d %d", &ex[i], &ey[i], &ez[i]);

		adjy[ex[i]][deg[ex[i]]] = ey[i];
		adjc[ex[i]][deg[ex[i]]++] = ez[i];

		adjy[ey[i]][deg[ey[i]]] = ex[i];
		adjc[ey[i]][deg[ey[i]]++] = ez[i];
	}

	dijkstra(ds, s);
	dijkstra(dt, t);

	memset(result, 0, sizeof(result));

	for (i = 1; i <= n; i++)
		av[i] = ((ds[i] + dt[i]) == ds[t]);

	for (i = 1; i <= n; i++)
		if (av[i])
			for (j = 1; j <= n; j++)
				if (av[j] && ds[j] == ds[i]) result[i]++;

	for (j = 0, i = 1; i <= n; i++)
		if (av[i]) ax[j++] = ds[i];
	qsort(ax, j, sizeof(ax[0]), &cmp);
	for (i = 0, an = 0; i < j; i++)
		if (i == 0 || ax[i-1] != ax[i]) ax[an++] = ax[i];
	ax[an] = INF;
	memset(ay, 0, sizeof(ay));

	for (i = 0; i < m; i++) {
		if ((ds[ex[i]] + ez[i] + dt[ey[i]]) == ds[t])
			add(ds[ex[i]]+1, ds[ey[i]]-1);

		if ((ds[ey[i]] + ez[i] + dt[ex[i]]) == ds[t])
			add(ds[ey[i]]+1, ds[ex[i]]-1);
	}

	for (i = 1; i <= n; i++)
		if (av[i]) result[i] += ay[bget(ax, an, ds[i])];

	for (i = 1; i <= n; i++)
		printf((i < n) ? "%d " : "%d\n", result[i]);

	return 0;
}
