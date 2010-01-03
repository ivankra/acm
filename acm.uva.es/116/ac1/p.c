#include <stdio.h>

int a[16][128], d[16][128], s[16][128], m, n;

int main()
{
	int i, j, k;

	while (scanf("%d %d", &m, &n) == 2 && n > 0) {
		for (i = 1; i <= m; i++)
			for (j = 1; j <= n; j++)
				scanf("%d", &a[i][j]);

		for (i = 1; i <= m; i++)
			d[i][n] = a[i][n];

		for (k = n - 1; k >= 1; k--) {
			for (i = 1; i <= m; i++) {
				j = (i == 1) ? m : (i - 1);
				d[i][k] = d[j][k + 1];
				s[i][k] = j;

				if ((d[i][k + 1] < d[i][k]) ||
				    (d[i][k + 1] == d[i][k] && s[i][k] > i)) {
					d[i][k] = d[i][k + 1];
					s[i][k] = i;
				}

				j = (i == m) ? 1 : (i + 1);
				if ((d[j][k + 1] < d[i][k]) ||
				    (d[j][k + 1] == d[i][k] && s[i][k] > j)) {
					d[i][k] = d[j][k + 1];
					s[i][k] = j;
				}

				d[i][k] += a[i][k];
			}
		}

		for (k = 1, i = 2; i <= m; i++)
			if (d[i][1] < d[k][1]) k = i;

		for (i = 1, j = k; i <= n; j = s[j][i++])
			printf((i == n) ? "%d\n" : "%d ", j);

		printf("%d\n", d[k][1]);
	}

	return 0;
}
