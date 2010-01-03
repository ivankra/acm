#include <stdio.h>
#include <string.h>

int a[10001], r, x, m, n;
int ncol[10001], col_row[10001][64], col_val[10001][64];

int main()
{
	int i, j;

	while (scanf("%d %d", &m, &n) == 2) {
		for(i=1;i<=n;i++)ncol[i]=0;

		for (i = 0; i < m && scanf("%d", &r) == 1; i++) {
			for (j = 0; j < r; j++)
				scanf("%d", &a[j]);

			for (j = 0; j < r; j++) {
				scanf("%d", &x);
				col_row[a[j]][ncol[a[j]]] = i+1;
				col_val[a[j]][ncol[a[j]]] = x;
				ncol[a[j]]++;
			}
		}

		printf("%d %d\n", n, m);
		for (i = 1; i <= n; i++) {
			printf("%d", ncol[i]);
			for (j = 0; j < ncol[i]; j++)
				printf(" %d", col_row[i][j]);
			printf("\n");

			for (j = 0; j < ncol[i]; j++)
				printf(j ? " %d" : "%d", col_val[i][j]);
			printf("\n");
		}
	}

	return 0;
}
