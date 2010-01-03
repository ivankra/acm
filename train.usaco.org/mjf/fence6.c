/*
ID: mjf28791
PROG: fence6
LANG: C
*/
#include <stdio.h>

#define INF 0x3fffffff

int len[128], adj[128][32], deg[128], deg1[128], n;

int check(int z)
{
	static int d[128], p[128], v[128];
	int i, j;

	for (i = 1; i <= n; i++)
		d[i] = INF, p[i] = -1, v[i] = 0;

	for (i = 0; i < deg1[z]; i++) {
		d[adj[z][i]] = len[z] + len[adj[z][i]];
		p[adj[z][i]] = z;
	}

	for (;;) {
		for (i = 1; i <= n && v[i]; i++);
		if (i > n) break;

		for (j = i + 1; j <= n; j++)
			if (v[j] == 0 && d[j] < d[i]) i = j;

		if (i == z || d[i] == INF)
			break;

		for (v[i] = 1, j = 0; j < deg[i]; j++) {
			if (p[i] == z && adj[i][j] == z)
				continue;

			if (d[adj[i][j]] > (d[i] + len[i] + len[adj[i][j]])) {
				d[adj[i][j]] = d[i] + len[i] + len[adj[i][j]];
				p[adj[i][j]] = i;
			}
		}
	}

	return d[z];
}

int main()
{
	int i, j, n1, n2, s;

	freopen("fence6.in", "r", stdin);
	freopen("fence6.out", "w", stdout);

	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		scanf("%d", &s);
		scanf("%d %d %d", &len[s], &n1, &n2);

		deg1[s] = n1;
		for (deg[s] = 0, j = 0; j < n1; j++)
			scanf("%d", &adj[s][deg[s]++]);

		for (j = 0; j < n2; j++)
			scanf("%d", &adj[s][deg[s]++]);
	}

	for (s = INF, i = 1; i <= n; i++)
		if ((j = check(i)) < s) s = j;

	printf("%d\n", s / 2);

	return 0;
}
