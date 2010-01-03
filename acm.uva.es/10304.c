#include <stdio.h>
#include <string.h>

int main()
{
	static int a[256], s[256], c[256][256], n, k, m;
	register int i, j, t;

	while (scanf("%d", &n) == 1) {
		for (i = 1, s[0] = s[1] = 0; i <= n; i++) {
			scanf("%d", &a[i]);
			s[i + 1] = s[i] + a[i];
		}

		for (i = 0; i <= n; i++)
			c[0][i] = c[1][i] = 0;

		for (k = 2; k <= n; k++) {
			m = n - k + 1;
			for (i = 1; i <= m; i++) {
				c[k][i] = c[k - 1][i + 1] - a[i];

				for (j = 1; j < k; j++) {
					t = c[j][i] + c[k - j - 1][i + j + 1] - a[i + j];
					if (t < c[k][i]) c[k][i] = t;

				}

				c[k][i] += s[i + k] - s[i];
			}
		}

		printf("%d\n", c[n][1]);
	}

	return 0;
}
