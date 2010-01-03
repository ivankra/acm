#include <stdio.h>

int main()
{
	static int a[16][16], d[16], n, m;
	int i, j;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0; i < n; i++)
			scanf("%d", &a[0][i]);
		scanf("%d", &m);

		for (i = 1; i < n; i++)
			for (j = 0; (i + j) < n; j++)
				a[i][j] = a[i - 1][j + 1] - a[i - 1][j];

		for (i = 0; i < n; i++)
			d[i] = a[i][n - i - 1];

		for (i = 0; i < m; i++)
			for (j = n - 2; j >= 0; j--)
				d[j] += d[j + 1];

		printf("Term %d of the sequence is %d\n", n + m, d[0]);
	}

	return 0;
}
