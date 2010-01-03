#include <stdio.h>
#include <string.h>

int a[256], n;

long long solve(int k, int m)
{
	static long long z[256][16][32];
	static int b[256];
	int i, j, r;

	if (k > n)
		return 0;

	memset(z, 0, sizeof(z));

	for (i = 0; i <= n; i++)
		z[i][0][0] = 1;

	for (i = 1; i <= n; i++)
		b[i] = m - (a[i - 1] % m);

	for (i = 1; i <= n; i++)
		for (j = 1; j <= k; j++)
			for (r = 0; r < m; r++)
				z[i][j][r] = z[i - 1][j][r] +
				             z[i - 1][j - 1][(r + b[i]) % m];

	return z[n][k][0];
}

int main()
{
	int i, t, q, k, m;

	for (t = 1; scanf("%d %d", &n, &q) == 2 && n > 0; t++) {
		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);

		printf("SET %d:\n", t);
		for (i = 1; i <= q && scanf("%d %d", &m, &k) == 2; i++)
			printf("QUERY %d: %lld\n", i, solve(k, m));
	}

	return 0;
}
