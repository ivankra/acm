#include <stdio.h>
#include <string.h>

#define INF 0x3fffffff

int adj[512][32], cap[512][32], n;
int dist[512], pos[512], heap[512], m;

static void up(int p)
{
	int d, t;

	for (d = dist[t = heap[p]]; p > 1 && dist[heap[p >> 1]] > d; p >>= 1)
		pos[heap[p] = heap[p >> 1]] = p;
	pos[heap[p] = t] = p;
}

static void down(int p)
{
	int i, j, d;

	for (d = dist[heap[p]]; (p << 1) <= m; p = i) {
		i = (dist[heap[p << 1]] < d) ? (p << 1) : p;
		j = (p << 1) | 1;
		if (j <= m && dist[heap[j]] < dist[heap[i]]) i = j;

		if (i == p) break;

		j = heap[i];
		pos[heap[i] = heap[p]] = i;
		pos[heap[p] = j] = p;
	}
}

static void find()
{
	int i, j, u;

	while (m > 0) {
		u = heap[1];
		pos[heap[1] = heap[m--]] = 1;

		if (m > 0)
			down(1);

		for (i = 0; (j = adj[u][i]) != 0; i++) {
			if ((dist[u] + cap[u][i]) < dist[j]) {
				if (dist[j] == INF) {
					m++;
					pos[heap[m] = j] = m;
				}

				dist[j] = dist[u] + cap[u][i];
				up(pos[j]);
			}
		}
	}
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int min(int a, int b)
{
	return (a < b) ? a : b;
}

int main()
{
	static char s[1024];
	static int deg[512], ex[512], sh[512];
	int i, j, t, w, x, y, z;

	while (gets(s) && sscanf(s, "%d", &t) != 1);

	while (t-- > 0 && scanf("%d %d", &x, &n) == 2) {
		memset(deg, 0, sizeof(deg));
		memset(ex, 0, sizeof(ex));

		while (x-- > 0 && scanf("%d", &y) == 1)
			ex[y] = 1;

		while ((i = getchar()) != EOF && i != '\n');

		while (gets(s) && sscanf(s, "%d %d %d", &x, &y, &z) == 3) {
			cap[x][deg[x]] = cap[y][deg[y]] = z;
			adj[x][deg[x]++] = y;
			adj[y][deg[y]++] = x;
		}

		for (i = 1; i <= n; i++)
			adj[i][deg[i]] = 0;

		for (m = 0, i = 1; i <= n; i++) {
			if (ex[i]) {
				dist[i] = 0;
				m++;
				pos[heap[m] = i] = m;
			} else {
				dist[i] = INF;
			}
		}

		find();

		for (i = 1; i <= n; i++)
			sh[i] = dist[i];

		for (w = 0, j = 1; j <= n; j++)
			if (sh[j] > w) w = sh[j];

		for (i = 1; i <= n; i++)
			if (ex[i]) { ex[i] = -ex[i]; break; }

		for (i = 1, z = INF, x = 0; i <= n; i++) {
			if (ex[i] > 0 || ((w - sh[i]) >= z)) continue;

			if (ex[i] < 0) {
				y = w;
			} else {
				for (j = 1; j <= n; j++) dist[j] = INF;
				dist[i] = 0;
				pos[heap[m = 1] = i] = 1;

				find();

				for (y = 0, j = 1; j <= n; j++)
					y = max(y, min(dist[j], sh[j]));
			}

			if (y < z)
				z = y, x = i;
		}

		printf(t ? "%d\n\n" : "%d\n", x);
	}

	return 0;
}
