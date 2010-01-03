#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *p, const void *q)
{
	return memcmp(p, q, 3 * sizeof(int));
}

int main()
{
	static int adj[128][128], r[1048576][3];
	int i, j, k, n, m;

	while (scanf("%d", &n) == 1) {
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				scanf("%d", &adj[i][j]);

		for (m = 0, i = 1; i < n; i++) {
			for (j = i + 1; j < n; j++) {
				if (!adj[i][j]) continue;
				for (k = j + 1; k <= n; k++) {
					if (!adj[j][k] || !adj[k][i]) continue;
					r[m][0] = i; r[m][1] = j; r[m++][2] = k;
				}
			}
		}


		for (i = n; i > 1; i--) {
			for (j = i - 1; j > 1; j--) {
				if (!adj[i][j]) continue;
				for (k = j - 1; k >= 1; k--) {
					if (!adj[j][k] || !adj[k][i]) continue;
					r[m][0] = i; r[m][1] = j; r[m++][2] = k;
				}
			}
		}

		qsort(r, m, sizeof(int) * 3, &compare);

		for (i = 0; i < m; i++)
			printf("%d %d %d\n", r[i][0], r[i][1], r[i][2]);
		printf("total:%d\n\n", m);
	}

	return 0;
}
