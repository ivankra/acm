#include <stdio.h>
#include <assert.h>

#define N 16384
#define M 1048576

int next[M], ref[M], adj[N], deg[N], n;

int bfs(int x, int y)
{
	static int q[N], d[N];
	int i, j, k, h, t;

	for (i = 0; i <= n; i++) d[i] = -1;

	for (i = 1; i <= n; i++)
		if (deg[i] == 2) d[i] = -2;

	d[q[0]=x] = 0;
	for (h = 0, t = 1; h < t && d[y] < 0; h++)
		for (i = adj[x = q[h]]; i != 0; i = next[i])
			if (d[ref[i]] == -1)
				d[q[t++] = ref[i]] = d[x] + 1;

	return d[y];
}

int main()
{
	int i, j, t, m, x, y;

	while (scanf("%d %d", &n, &m) == 2 && n > 0) {
		for (i = 0; i <= n; i++) adj[i] = deg[i] = 0;

		for (i = 1; m-- > 0 && scanf("%d %d", &x, &y) == 2;) {
			ref[i] = y; next[i] = adj[x]; adj[x] = i++;
			ref[i] = x; next[i] = adj[y]; adj[y] = i++;
			deg[x]++; deg[y]++;
		}

		for (i = 1; i <= n; i++)
			if (deg[i] <= 1) break;
		if (i <= n) {
			printf("Poor Koorosh\n");
			continue;
		}

		for (i = 1, j = 0; i <= n; i++) j += (deg[i] & 1);

		assert(j <= 2);

		if (j == 0) {
			printf("0\n");
			continue;
		} else if (j == 1) {
			printf("Poor Koorosh\n");
			continue;
		}

		for (x = 1; (deg[x] & 1) == 0; x++);
		for (y = x+1; (deg[y] & 1) == 0; y++);

		i = bfs(x,y);
		if (i < 0) {
			printf("Poor Koorosh\n");
		} else {
			printf("%d\n", i);
		}
	}

	return 0;
}
