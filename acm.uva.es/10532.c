#include <stdio.h>

int main()
{
	static unsigned long long c[64][64];
	static int a[64], n, m, x, t;
	register int i, j, k;

	for (t = 1; scanf("%d %d", &n, &m) == 2 && n > 0; t++) {
		memset(a, '\0', sizeof(a));

		for (i = 0; i < n && scanf("%d", &x); i++)
			if (x >= 1 && x <= n) a[x]++;

		for (c[0][0] = 1, i = 1; i <= n; i++)
			c[0][i] = 0;

		for (i = 1; i <= n; i++) {
			for (c[i][0] = 1, j = 1; j <= n; j++) {
				c[i][j] = 0;
				for (k = 0; k <= a[i] && (j - k) >= 0; k++)
					c[i][j] += c[i - 1][j - k];
			}
		}

		printf("Case %d:\n", t);

		while (m-- > 0 && scanf("%d", &x) == 1)
			if (x < 0 || x > n)
				printf("0\n");
			else
				printf("%llu\n", c[n][x]);
	}

	return 0;
}
