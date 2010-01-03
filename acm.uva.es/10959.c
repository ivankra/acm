#include <stdio.h>

#define INF 0x7FFFFFFF
#define N 1024
#define M (512*1024)

int main()
{
	static int adj[N], next[M], ref[M], d[N], q[N], n;
	int i, j, t, m, x, y;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &m) == 2;) {
		for (i = 0; i <= n; i++) adj[i] = 0;

		for (j = 1; m-- > 0 && scanf("%d %d", &x, &y) == 2;) {
			if (x == y) continue;
			ref[j] = y; next[j] = adj[x]; adj[x] = j; j++;
			ref[j] = x; next[j] = adj[y]; adj[y] = j; j++;
		}

		for (i = 0; i <= n; i++) d[i] = INF;
		d[0] = 0;
		q[0] = 0;
		for (i = 0, m = 1; i < m; i++)
			for (j = adj[q[i]]; j != 0; j = next[j])
				if (d[ref[j]] >= INF)
					d[q[m++] = ref[j]] = d[q[i]] + 1;

		for (i = 1; i < n; i++)
			printf("%d\n", d[i]);

		if (t) printf("\n");
	}

	return 0;
}
