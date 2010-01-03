#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

int x[16], y[16], n;
double d[16][16];

char got[65536];
double tab[65536];

double f(int m)
{
	int s, i;
	double t;

	if (got[m]) return tab[m];
	got[m] = 1;

	for (s = 0; s < n && ((m >> s) & 1) != 0; s++);
	if (s == n) return tab[m] = 0.;

	for (tab[m] = 1./0., i = s + 1; i < n; i++) {
		if ((m >> i) & 1) continue;
		t = d[s][i] + f(m ^ (1 << i) ^ (1 << s));
		if (t < tab[m]) tab[m] = t;
	}

	return tab[m];
}

int main()
{
	int i, j, t;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		assert(n <= 8);

		n *= 2;
		for (i = 0; i < n; i++)
			scanf(" %*s %d %d", &x[i], &y[i]);

		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				d[i][j] = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));

		memset(got, 0, sizeof(got));
		printf("Case %d: %.2f\n", t, f(0));
	}

	return 0;
}
