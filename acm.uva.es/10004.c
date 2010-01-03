#include <stdio.h>
#include <string.h>

int main()
{
	static int n, m, a, b, adj[256][256], c[256], v[256], q[256];
	int i;

	while (scanf("%d %d", &n, &m) == 2 && n > 0) {
		memset(adj, 0, sizeof(adj));

		while (m-- > 0 && scanf("%d %d", &a, &b) == 2)
			adj[a][b] = adj[b][a] = 1;

		for (v[0] = 1, i = 1; i < n; i++)
			v[i] = 0;

		c[0] = 0;
		q[0] = 0;
		m = 1;

		/* depth-first search */

		while (m > 0) {
			a = q[--m];

			for (i = 0; i < n; i++) {
				if (adj[a][i] == 0)
					continue;

				if (v[i]) {
					if (c[i] == c[a]) break;
				} else {
					v[i] = 1;
					c[i] = c[a] ^ 1;
					q[m++] = i;
				}
			}

			if (i < n)
				break;
		}

		printf(m ? "NOT BICOLORABLE.\n" : "BICOLORABLE.\n");
	}

	return 0;
}
