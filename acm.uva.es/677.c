#include <stdio.h>
#include <string.h>

int adj[16][16], w[256], u[16], n, m, r;

void find(int k)
{
	if (k > m) {
		printf("(%d", w[0]);
		for (r++, k = 1; k <= m; k++)
			printf(",%d", w[k]);
		printf(")\n");
		return;
	}

	for (w[k] = 1; w[k] <= n; w[k]++) {
		if (u[w[k]] == 0 && adj[w[k - 1]][w[k]]) {
			u[w[k]] = 1;
			find(k + 1);
			u[w[k]] = 0;
		}
	}
}

int main()
{
	int i, j, t;

	for (t = 0; scanf("%d %d", &n, &m) == 2 && n > 0; t++) {
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				scanf("%d", &adj[i][j]);
		scanf("%*d");

		if (t != 0)
			printf("\n");

		r = 0;

		memset(u, 0, sizeof(u));
		u[1] = 1;

		w[0] = 1;
		find(1);

		if (r == 0)
			printf("no walk of length %d\n", m);
	}

	return 0;
}
