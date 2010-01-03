#include <stdio.h>
#include <string.h>

int got[128][128], m;
double tab[128][128], r[128][128];

double f(int n, int k)
{
	if (got[n][k]) return tab[n][k];
	got[n][k] = 1;
	if (n == 0)
		tab[n][k] = (k == 0) ? 0. : 1.;
	else
		tab[n][k] = ((m - k) * f(n - 1, k) + k * f(n - 1, k - 1)) / (double)m;
	return tab[n][k];
}

int main()
{
	int n, t;

	for (m = 0; m <= 100; m++) {
		memset(got, 0, sizeof(got));
		for (n = 0; n <= 100; n++)
			r[n][m] = f(n, m);
	}

	for (t = 1; scanf("%d %d", &n, &m) == 2 && n >= 0; t++)
		printf("Case %d: %.7f\n", t, r[n][m]);

	return 0;
}
