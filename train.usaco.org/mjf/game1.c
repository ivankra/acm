/*
ID: mjf28791
PROG: game1
LANG: C
*/
#include <stdio.h>

int main()
{
	static int rx[256][256], ry[256][256], c[256], n;
	int i, j, k;

	freopen("game1.in", "r", stdin);
	freopen("game1.out", "w", stdout);

	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d", &c[i]);

	for (i = 0; i < n; i++) {
		rx[1][i] = c[i];
		ry[1][i] = 0;
	}

	for (i = 2; i <= n; i++) {
		for (j = 0; (j + i) <= n; j++) {
			k = ry[i - 1][j + 1] + c[j];
			k -= ry[i - 1][j] + c[i + j - 1];

			if (k > 0 || (k == 0 && ry[i - 1][j + 1] < ry[i - 1][j])) {
				rx[i][j] = ry[i - 1][j + 1] + c[j];
				ry[i][j] = rx[i - 1][j + 1];
			} else {
				rx[i][j] = ry[i - 1][j] + c[i + j - 1];
				ry[i][j] = rx[i - 1][j];
			}
		}
	}

	printf("%d %d\n", rx[n][0], ry[n][0]);
	return 0;
}
