#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int d[32][32], u[32], n, s, mincost;

void find(int m, int x, int cost)
{
	int i;

	if ((cost + d[x][1]) >= mincost)
		return;

	if (m == s) {
		mincost = cost + d[x][1];
		return;
	}

	for (i = 2; i < n; i++) {
		if (u[i]) continue;
		u[i] = 1;
		find(m + 1, i, cost + d[x][i]);
		u[i] = 0;
	}
}

int main()
{
	int x[32], y[32], i, j, t, dim;

	for (t = 1; scanf("%d %d %d", &dim, &n, &s) == 3 && dim > 0; t++) {
		n += 2;
		x[0] = y[0] = 0;
		x[1] = y[1] = dim - 1;
		for (i = 2; i < n; i++)
			scanf("%d %d", &x[i], &y[i]);

		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				d[i][j] = abs(x[i] - x[j]) + abs(y[i] - y[j]);

		memset(u, 0, sizeof(u));
		mincost = 0x7FFFFFFF;

		find(0, 0, 0);

		printf("Case %d: %d\n", t, mincost);
	}

	return 0;
}
