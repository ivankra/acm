/*
ID: mjf28791
PROG: stall4
LANG: C
*/
#include <stdio.h>
#include <string.h>

int adj[256][256], deg[256], m, n;

int match()
{
	static int p[256], s[256], tm[256], tn[256], f, r, z;
	int i, j, k, t;

	for (i = 0; i < m; i++)
		tm[i] = -1;

	for (i = 0; i < n; i++)
		tn[i] = -1;

	for (r = 0;; r += f) {
		for (i = 0; i < m; i++)
			p[i] = (tm[i] < 0) ? i : -1;

		for (f = 0, z = 0; z < m; z++) {
			if (tm[z] >= 0) continue;

			for (s[0] = z, t = 1; t > 0;)
				for (i = s[--t], j = 0; j < deg[i]; j++)
					if (tn[k = adj[i][j]] < 0) {
						for (f++, t = 0;; i = p[i]) {
							j = tm[tn[k] = i];
							tm[i] = k;
							if ((k = j) < 0) break;
						}
						break;
					} else if (p[tn[k]] < 0) {
						p[s[t++] = tn[k]] = i;
					}
		}

		if (f == 0)
			return r;
	}
}

int main()
{
	int i, j;

	freopen("stall4.in", "r", stdin);
	freopen("stall4.out", "w", stdout);

	scanf("%d %d", &m, &n);
	for (i = 0; i < m && scanf("%d", &deg[i]) == 1; i++)
		for (j = 0; j < deg[i] && scanf("%d", &adj[i][j]) == 1; j++)
			adj[i][j]--;

	printf("%d\n", match());
	return 0;
}
