#include <stdio.h>
#include <stdlib.h>

int d[256], sum[256];
int ftab[256][32], ftabc[256][32];

int cost(int a, int b)
{
	int c, m, t;

	for (m = 0x3FFFFFFF, c = a; c < b; c++) {
		t = (2 * c - a - b) * d[c] - 2 * sum[c] + sum[a] + sum[b];
		if (t < m) m = t;
	}

	return m;
}

int choose(int a, int b)
{
	int c, m, t, r;

	for (m = 0x3FFFFFFF, r = a, c = a; c < b; c++) {
		t = (2 * c - a - b) * d[c] - 2 * sum[c] + sum[a] + sum[b];
		if (t < m) m = t, r = c; 
	}

	return r;
}

int f(int n, int k)
{
	int i, t;

	if (k == 0)
		return (n == 0) ? 0 : 0x3FFFFFFF;

	if (ftab[n][k] >= 0)
		return ftab[n][k];

	for (ftab[n][k] = 0x3FFFFFFF, i = k - 1; i < n; i++) {
		t = f(i, k - 1) + cost(i, n);
		if (t < ftab[n][k]) {
			ftab[n][k] = t;
			ftabc[n][k] = i;
		}
	}

	return ftab[n][k];
}

int main()
{
	static int da[32], db[32];
	int i, j, n, k, t;

	for (t = 1; scanf("%d %d", &n, &k) == 2 && n > 0; t++) {
		for (i = 0; i < n; i++)
			scanf("%d", &d[i]);

		for (sum[0] = 0, i = 0; i < n; i++)
			sum[i + 1] = sum[i] + d[i];

		for (i = 0; i <= n; i++)
			for (j = 0; j <= k; j++)
				ftab[i][j] = -1;

		f(n, k);

		for (i = n, j = k; j > 0; j--) {
			da[j] = ftabc[i][j];
			db[j] = i;
			i = ftabc[i][j];
		}

		printf("Chain %d\n", t);
		for (i = 1; i <= k; i++) {
			printf("Depot %d at restaurant %d serves ",
				i, choose(da[i], db[i]) + 1);

			if (da[i] == (db[i] - 1))
				printf("restaurant %d\n", da[i] + 1);
			else
				printf("restaurants %d to %d\n",
					da[i] + 1, db[i]);
		}
		printf("Total distance sum = %d\n\n", f(n, k));
	}

	return 0;
}
