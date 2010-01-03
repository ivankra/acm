#include <stdio.h>
#include <string.h>

int main()
{
	static int a[1024], sum[1024], rx[128][128], ry[128][128], n;
	int i, k, m, s, t;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0, sum[0] = 0; i < n; i++) {
			scanf("%d", &a[i]);
			sum[i + 1] = sum[i] + a[i];
		}

		memset(rx, 0, sizeof(rx));
		memset(ry, 0, sizeof(ry));

		for (m = 1; m <= n; m++) {
			for (k = 0; (k + m) <= n; k++) {
				rx[m][k] = a[k] + ry[m - 1][k + 1];

				for (s = 0, i = 1; i <= m; i++) {
					s += a[k + i - 1];
					t = s + ry[m - i][k + i];
					if (t > rx[m][k]) rx[m][k] = t;
				}

				for (s = 0, i = 1; i <= m; i++) {
					s += a[k + m - i];
					t = s + ry[m - i][k];
					if (t > rx[m][k]) rx[m][k] = t;
				}

				ry[m][k] = sum[k + m] - sum[k] - rx[m][k];
			}
		}

		printf("%d\n", rx[n][0] - ry[n][0]);
	}

	return 0;
}
