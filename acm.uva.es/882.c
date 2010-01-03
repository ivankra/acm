#include <stdio.h>

int tab[16][128][128];

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int f(int k, int a, int b)
{
	int c, r, t;

	if (tab[k][a][b] >= 0)
		return tab[k][a][b];

	for (r = 0x7FFFFFFF, c = a + 1; c <= b; c++) {
		t = max(f(k - 1, a, c - 1), f(k, c, b)) + c;
		if (t < r) r = t;
	}

	return (tab[k][a][b] = r);
}

int main()
{
	int i, j, k, m, t;

	for (k = 2; k <= 10; k++) {
		for (i = 0; i <= 100; i++) {
			for (j = 0; j <= 100; j++)
				tab[k][i][j] = -1;
			tab[k][i][i] = 0;
		}
	}

	for (i = 0; i <= 100; i++)
		for (k = 0, j = i; j <= 100; k += ++j)
			tab[1][i][j] = k;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &k, &m) == 2;)
		printf("%d\n", f(k, 0, m));

	return 0;
}
