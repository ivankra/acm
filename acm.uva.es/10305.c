#include <stdio.h>

int main()
{
	static int adj[128][128], dep[128], m, n, x, y;
	int i, j;
	
	while (scanf("%d %d", &n, &m) == 2 && n > 0) {
		for (i = 1; i <= n; i++)
			for (dep[i] = 0, j = 1; j <= n; j++) adj[i][j] = 0;

		while (m-- > 0 && scanf("%d %d", &x, &y) == 2) {
			if (x != y && adj[x][y] == 0) {
				adj[x][y] = 1;
				dep[y]++;
			}
		}

		for (m = 0;; m++) {
			for (i = 1; i <= n; i++)
				if (dep[i] == 0) break;

			if (i > n)
				break;

			printf(m ? " %d" : "%d", i);

			for (j = 1; j <= n; j++)
				if (adj[i][j]) dep[j]--;

			dep[i] = -1;
		}

		printf("\n");		
	}

	return 0;
}
