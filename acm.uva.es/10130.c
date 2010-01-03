#include <stdio.h>
#include <string.h>

int main()
{
	static int p[1024], w[1024], z[32][1024], n, t, x;
	int i, k;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (i = 1; i <= n; i++)
			scanf("%d %d", &p[i], &w[i]);

		memset(z, 0, sizeof(z));
		for (k = 1; k <= 30; k++) {
			for (z[k][0] = 0, i = 1; i <= n; i++) {
				z[k][i] = z[k][i - 1];

				if (w[i] <= k && (p[i] + z[k - w[i]][i - 1]) > z[k][i])
					z[k][i] = (p[i] + z[k - w[i]][i - 1]);
			}
		}

		for (i = 0; i <= 30; i++)
			p[i] = z[i][n];

		for (scanf("%d", &n), i = 0; n-- > 0 && scanf("%d", &x) == 1;)
			i += p[x];

		printf("%d\n", i);
	}

	return 0;
}
