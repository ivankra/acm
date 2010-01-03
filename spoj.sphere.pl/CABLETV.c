#include <stdio.h>
#include <string.h>

#define V_IN(v)  (2 * (v))
#define V_OUT(v) (2 * (v) + 1)

int adj[128][128], r[128][128], nvert;

int maxflow(int s, int t)
{
	static int v[128], p[128], q[128], qh, qt;
	int i, j, flow;

	for (i = 0; i < nvert; i++)
		for (j = 0; j < nvert; j++)
			r[i][j] = adj[i][j];

	for (flow = 0;; flow++) {
		memset(v, 0, sizeof(v));

		for (q[qh = 0] = s, qt = 1, v[s] = 1; qh < qt && v[t] == 0;) {
			for (i = q[qh++], j = 0; j < nvert; j++) {
				if (r[i][j] && v[j] == 0) {
					v[j] = 1;
					p[j] = i;
					q[qt++] = j;
				}
			}
		}

		if (v[t] == 0)
			break;

		for (i = t; i != s; i = p[i]) {
			r[p[i]][i] = 0;
			r[i][p[i]] = 1;
		}
	}

	return flow;
}

int main()
{
	int i, j, n, m, x, y, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &m) == 2;) {
		nvert = 2 * n;
		memset(adj, 0, sizeof(adj));

		for (i = 0; i < n; i++)
			adj[V_IN(i)][V_OUT(i)] = 1;

		for (j = 0; m-- > 0 && scanf(" ( %d , %d )", &x, &y) == 2;) {
			if (x != y && adj[V_OUT(x)][V_IN(y)] == 0) {
				adj[V_OUT(x)][V_IN(y)] = 1;
				adj[V_OUT(y)][V_IN(x)] = 1;
				j++;
			}
		}

		if (n == 0 || j >= (n * (n - 1) / 2)) {
			printf("%d\n", n);
			continue;
		}

		for (m = -1, x = 0; x < n; x++) {
			for (y = x + 1; y < n; y++) {
				i = maxflow(V_OUT(x), V_IN(y));
				if (m < 0 || i < m)
					m = i;
			}
		}

		printf("%d\n", (m < 0) ? 0 : m);
	}

	return 0;
}
