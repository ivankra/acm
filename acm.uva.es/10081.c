#include <stdio.h>

/* k (base 1..10), a0 (first digit 1..k), n (length 0..100) */
static double tab[16][16][128];

static void make()
{
	register int a, k, n;

	for (k = 1; k <= 10; k++) {
		for (a = 0; a < 11; a++) {
			tab[k][a][0] = 0.;
			tab[k][a][1] = 1. / (double)k;
		}

		for (n = 2; n <= 101; n++) {
			tab[k][0][n - 1] = tab[k][k + 1][n - 1] = 0.;
			for (a = 1; a <= k; a++)
				tab[k][a][n] =
					(tab[k][a - 1][n - 1] +
					 tab[k][a][n - 1] +
					 tab[k][a + 1][n - 1]) / (double)k;
		}
	}
}

int main()
{
	int n, k, i;
	double p;

	make();

	while (scanf("%d%d", &k, &n) == 2) {
		k++;
		for (i = 1, p = 0.; i <= k; i++)
			p += tab[k][i][n];

		printf("%.5f\n", p * 100.0);
	}

	return 0;
}
