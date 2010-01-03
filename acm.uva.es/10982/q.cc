#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
	int G[128][128];
	int n, m, x, y, T, cs = 1;

	scanf("%d", &T);
	for (cs = 1; cs <= T && scanf("%d %d", &n, &m) == 2; cs++) {
		memset(G, 0, sizeof(G));

		while (m-- > 0 && scanf("%d %d", &x, &y) == 2) {
			G[x][y] = G[y][x] = 1;
		}

                /* G[u][v] = 1, if there is edge (u,v) in the graph */

                int where[128];
		for (int i = 1; i <= n; i++) {
			int a = 0, b = 0;

			for (int j = 1; j < i; j++)
				if (where[j] == 0)
					a += G[i][j];
				else
					b += G[i][j];

			where[i] = (a <= b) ? 0 : 1;
		}

                /* output all vertices i, such that where[i]=0 */

int P=0;
		x = 0;
		for (int i = 1; i <= n; i++) if (where[i] == P) x++;
		printf("Case #%d: %d\n", cs, x);
		x = 0;
		for (int i = 1; i <= n; i++)
			if (where[i] == P)
				printf(x++ ? " %d" : "%d", i);
		printf("\n");
	}

	return 0;
}
