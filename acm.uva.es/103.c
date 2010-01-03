#include <stdio.h>

static void sort(int a[], int n)
{
	register int i, j, t;

	for (i = 1; i < n; i++) {
		for (t = a[i], j = i - 1; j >= 0 && a[j] > t; j--)
			a[j + 1] = a[j];
		a[j + 1] = t;
	}
}

int main()
{
	int dim[32][16], nests[32][32], len[32][32], succ[32][32], n, d, x, y;
	int i, j, k;

	while (scanf("%d %d", &n, &d) == 2) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < d; j++)
				scanf("%d", &dim[i][j]);
			sort(dim[i], d);
		}

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				for (k = 0; k < d; k++)
					if (dim[i][k] >= dim[j][k]) break;

				nests[i][j] = (k >= d);
			}
			nests[i][i] = 0;
		}

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (nests[i][j]) {
					len[i][j] = 1;
					succ[i][j] = j;
				} else {
					len[i][j] = 0;
					succ[i][j] = -1;
				}
			}
		}

		for (k = 0; k < n; k++) {
			for (i = 0; i < n; i++) {
				if (i == k || len[i][k] == 0)
					continue;

				for (j = 0; j < n; j++) {
					if (len[k][j] == 0)
						continue;

					if ((len[i][k]+len[k][j]) > len[i][j]){
						len[i][j]=len[i][k]+len[k][j];
						succ[i][j] = succ[i][k];
					}
				}
			}
		}

		for (i = 0, k = x = y = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (len[i][j] > k) k = len[x = i][y = j];

		printf("%d\n", k + 1);
		for (k = 0; x >= 0; k++, x = succ[x][y]) {
			printf(k ? " %d" : "%d", x + 1);
			if (x == y) break;
		}
		printf("\n");
	}

	return 0;
}
