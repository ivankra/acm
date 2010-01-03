#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int adj[128][128], d[128], low[128], n, tm, r;

void dfs(int p, int x)
{
	int a, k, y;

	low[x] = d[x] = tm++;
	for (a = 0, k = 0, y = 1; y <= n; y++) {
		if (adj[x][y] == 0 || y == p || x == y)
			continue;

		if (d[y] != 0) {
			if (d[y] < low[x])
				low[x] = d[y];
		} else {
			k++;

			dfs(x, y);

			if (low[y] < low[x])
				low[x] = low[y];

			if (low[y] >= d[x])
				a = 1;
		}
	}

	if ((p == 0 && k >= 2) || (p != 0 && a))
		r++;
}

int main()
{
	static char s[65536];
	char *p;
	int k, x;

	while (scanf("%d", &n) == 1 && n > 0) {
		memset(adj, 0, sizeof(adj));

		while (scanf("%d%[^\n]", &x, s) > 0 && x > 0) {
			for (k = 0; (p = strtok(k++ ? NULL : s, " ")) != NULL;)
				adj[x][atoi(p)] = adj[atoi(p)][x] = 1;
		}

		memset(d, 0, sizeof(d));
		for (r = 0, tm = 1, k = 1; k <= n; k++)
			if (d[k] == 0) dfs(0, k);

		printf("%d\n", r);
	}

	return 0;
}
