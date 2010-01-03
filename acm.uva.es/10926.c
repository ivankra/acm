#include <stdio.h>

int adj[128][128], deg[128], dep[128], s[128], v[128], n;

int f(int x)
{
	int i, r, t;

	for (i = 1; i <= n; i++)
		v[i] = 0;

	for (v[s[0] = x], t = 1, r = 0; t-- > 0;)
		for (x = s[t], i = 0; adj[x][i]; i++)
			if (v[adj[x][i]] == 0) r++, v[s[t++] = adj[x][i]] = 1;

	return r;
}

int main()
{
	int i, j;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 1; i <= n && scanf("%d", &deg[i]) == 1; i++)
			for (adj[i][deg[i]] = 0, j = 0; j < deg[i]; j++)
				scanf("%d", &adj[i][j]);

		for (i = j = 1; i <= n; i++) {
			dep[i] = f(i);
			if (dep[i] > dep[j]) j = i;
		}

		printf("%d\n", j);
	}

	return 0;
}
