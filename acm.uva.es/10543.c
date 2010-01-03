#include <stdio.h>

int main()
{
	static int adj[64][64], p[64], q[64], n, m, k, x, y;
	int i, j, r;

	while (scanf("%d %d %d", &n, &m, &k) == 3 && n > 0) {
		memset(adj, 0, sizeof(adj));

		while (m-- > 0 && scanf("%d %d", &x, &y) == 2)
			if (x != y) adj[x][y] = 1;

		memset(p, 0, sizeof(p));
		p[0] = 1;

		for (r = 1; r <= 20; r++) {
			if (r >= k && p[n - 1])
				break;

			memset(q, 0, sizeof(q));

			for (i = 0; i < n; i++) {
				if (p[i] == 0)
					continue;

				for (j = 0; j < n; j++)
					if (adj[i][j]) q[j] = 1;
			}

			memcpy(p, q, sizeof(q));
		}

		printf((r > 20) ? "LOSER\n" : "%d\n", r);
	}

	return 0;
}
