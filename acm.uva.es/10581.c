#include <stdio.h>

long long tab[11][256][256];

void make()
{
	int i, j, k;

	for (i = 0; i < 256; i++)
		tab[0][0][i] = 1;

	for (k = 1; k <= 10; k++) {
		for (i = 1; i <= 220; i++) {
			tab[k][i][i] = tab[k - 1][0][i];
			for (j = i - 1; j >= 1; j--)
				tab[k][i][j] = tab[k-1][i-j][j] + tab[k][i][j+1];
		}
	}
}

int main()
{
	int a, m, n, k, s, t;

	make();
	for (scanf("%d", &t); t-- > 0 && scanf("%d %d %d", &m, &n, &k) == 3;) {
printf("[%lld]\n", tab[n][m][1]);
		for (a = 1; n > 0; n--, m -= a, k -= s) {
			for (s = 0; a < m && (s + tab[n - 1][m - a][a]) < k; a++)
				s += tab[n - 1][m - a][a];
			printf("%d\n", a);
		}
	}

	return 0;
}
