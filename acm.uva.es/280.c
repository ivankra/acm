#include <stdio.h>
#include <string.h>

int main()
{
	static int adj[128][128], q[128], r[128], n, a, b;
	register int i, k;

	while (scanf("%d", &n) == 1 && n != 0) {
		memset(adj, 0, sizeof(adj));

		while (scanf("%d", &a) == 1 && a != 0) {
			while (scanf("%d", &b) == 1 && b != 0) {
				adj[a][b] = 1;
			}
		}

		for (scanf("%d", &b); b-- > 0 && scanf("%d", &a) == 1;) {
			memset(r, 0, sizeof(r));

			q[0] = a;
			k = 1;

			while (k-- > 0) {
				a = q[k];

				for (i = 1; i <= n; i++) {
					if (adj[a][i] && r[i] == 0) {
						q[k++] = i;
						r[i] = 1;
					}
				}
			}

			for (i = 1, k = 0; i <= n; i++)
				if (r[i] == 0) k++;

			printf("%d", k);
			for (i = 1; i <= n; i++)
				if (r[i] == 0) printf(" %d", i);
			printf("\n");
		}
	}

	return 0;
}
