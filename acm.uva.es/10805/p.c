#include <stdio.h>
#include <string.h>

static int adj[32][32], n;
static int bfs1[32];

static int bfs2(int u1, int u2)
{
	static int v[32], q[32], m[32][32], d[32][32];
	register int k, i, j, t;

	memset(v, 0, sizeof(v));
	memset(m, 0, sizeof(m));

	k = 0;

	q[k++] = u1;
	v[u1] = 1;

	if (u2 != u1) {
		q[k++] = u2;
		v[u2] = 1;
		m[u1][u2] = m[u2][u1] = 1;
	}

	for (j = 0; j < k; j++) {
		t = q[j];

		for (i = 0; i < n; i++) {
			if (adj[t][i] && v[i] == 0) {
				v[i] = 1;
				q[k++] = i;
				m[t][i] = m[i][t] = 1;
			}
		}
	}

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			d[i][j] = (i == j) ? 0 : (m[i][j] ? 1 : 255);

	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			if (d[i][k] >= 255) continue;
			for (j = 0; j < i; j++) {
				t = d[i][k] + d[k][j];
				if (t < d[i][j])
					d[i][j] = d[j][i] = t;
			}
		}
	}

	for (k = 0, i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (d[i][j] > k) k = d[i][j];

	return k;
}

static int solve()
{
	int i, j, k, t;

	for (i = 0; i < n; i++)
		bfs1[i] = bfs2(i, i);

	for (i = 1, k = bfs1[0]; i < n; i++)
		if (bfs1[i] < k) k = bfs1[i];

	if (k <= 3 || (k & 1))
		return k;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j || adj[i][j] == 0)
				continue;

			t = bfs2(i, j);
			if (t < k)
				k = t;

			if (k & 1)
				return k;
		}
	}

	return k;
}

int main()
{
	static int a, b, c, t, m;

	scanf("%d", &c);
	for (t = 1; t <= c && scanf("%d %d", &n, &m) == 2; t++) {
		memset(adj, 0, sizeof(adj));

		while (m-- > 0 && scanf("%d %d", &a, &b) == 2)
			adj[a][b] = adj[b][a] = 1;

		printf("Case #%d:\n%d\n\n", t, solve());
	}

	return 0;
}
