#include <stdio.h>

/* match() -- finds maximum matching of a bipartite graph.

   Input: the vertices of the graph are separated into two group M, N.
   Vertices are labeled M_0, ..., M_{m-1}; N_0, ..., N_{n-1}.
   m = |M|, n = |N|.
   deg[i]: degree of M_i.
   adj[i]: adjacency list for vertex M_i.

   Output: the return value is the cardinality of maximum matching.
   tm[i], tn[i] -- index of the matched vertex in the other partition, or -1,
   if unmatched. */

#define MAXM	128
#define MAXN	128

int adj[MAXM][MAXN], deg[MAXM], m, n;
int tm[MAXM], tn[MAXN];

int match()
{
	static int p[MAXM], s[MAXM], f, r, z;
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
	int x, y;

	memset(deg, 0, sizeof(deg));
	for (m = n = 0; scanf("%d %d", &x, &y) == 2 && x >= 0 && y >= 0;) {
		if (x >= n) n = x + 1;
		if (y >= m) m = y + 1;
		adj[x][deg[x]++] = y;
	}

	printf("No. of matched edges: %d\n", match());
	for (x = 0; x < m; x++)
		if (tm[x] >= 0) printf("(%d, %d)\n", x, tm[x]);

	return 0;
}
