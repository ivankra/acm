#include <stdio.h>
#include <string.h>

int adj[128][128], e[128], n;

int solve()
{
	static int cl[128][128];
	static int d[128], c[128], q[4*65536];
	int i, j, k, *qh, *qt;

	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			cl[i][j] = adj[i][j];

	for (k = 1; k <= n; k++)
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				cl[i][j] |= cl[i][k] & cl[k][j];

	if (cl[1][n] == 0)
		return 0;

	memset(c, 0, sizeof(c));
	for (i = 1; i <= n; i++)
		c[i] = d[i] = 0;

	qh = qt = q;
	*qt++ = 1;
	d[1] = 100;

	while (qh < qt) {
		i = *qh++;

		if (i == n || adj[i][n])
			return 1;

		c[i]++;

		if (c[i] > (n + 3))
			return 1;

		for (j = 1; j < n; j++) {
			if (adj[i][j] && cl[j][n] && (d[i] + e[j]) > d[j]) {
				d[j] = d[i] + e[j];
				*qt++ = j;
			}
		}
	}

	return 0;
}

int main()
{
	int i, m, x;

	while (scanf("%d", &n) == 1 && n >= 0) {
		memset(adj, 0, sizeof(adj));

		for (i = 1; i <= n && scanf("%d %d", &e[i], &m) == 2; i++) {
			while (m-- > 0 && scanf("%d", &x) == 1)
				adj[i][x] = 1;
		}

		printf(solve() ? "winnable\n" : "hopeless\n");
	}

	return 0;
}
