#include <stdio.h>

int t1, t2, n;
int m[32], cost[32][32], a[32][512], p[32][512];

#define INF 0x000FFFFF

void solve()
{
	int i, j, k;

	for (i = 0; i <= m[0]; i++) {
		a[0][i] = cost[0][i];
		p[0][i] = i;
	}

	for (; i <= t1; i++)
		a[0][i] = INF;

	for (k = 1; k < n; k++) {
		for (i = 0; i <= t1; i++) {
			a[k][i] = INF;
			p[k][i] = 0;
			for (j = 0; j <= i && j <= m[k]; j++) {
				if ((cost[k][j] + a[k - 1][i - j]) >= a[k][i])
					continue;
				a[k][i] = cost[k][j] + a[k - 1][i - j];
				p[k][i] = j;
			}
		}
	}

	for (i = n - 1, j = t1; i >= 0; i--) {
		m[i] = p[i][j];
		j -= p[i][j];
	}

	printf("%d\n", a[n - 1][t1]);
	for (i = 0; i < n; i++)
		printf(((i + 1) == n) ? "%d\n" : "%d ", m[i]);
}


int main()
{
	int a[128], b[128], i, j;

	while (scanf("%d %d %d", &t1, &t2, &n) == 3 && (t1 + t2) > 0) {
		for (i = 0; i < n && scanf("%d", &m[i]) == 1; i++) {
			for (a[0] = 0, j = 1; j <= m[i]; j++)
				scanf("%d", &a[j]);

			for (b[0] = 0, j = 1; j <= m[i]; j++)
				scanf("%d", &b[j]);

			for (j = 0; j <= m[i]; j++)
				cost[i][j] = a[j] + b[m[i] - j];
		}

		solve();
	}

	return 0;
}
