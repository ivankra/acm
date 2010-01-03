#include <stdio.h>
#include <string.h>
#include <math.h>

double m0, len[32], tab[32][32];
int got[32][32], n;

double f(int k, int c)
{
	double m, s, v, c1;

	if (k >= n) return 0;
	if (got[k][c]) return tab[k][c];

	m = m0 - c;
	s = len[k];

	c1 = (s / 10. + 10. + f(k + 1, c + 1) - f(k + 1, c)) / m;

	v = sqrt(s / c1);
	if ((c1 * m + s / m) < (c1 * v + s / v)) v = m;

	if (v > m) v = m;

	got[k][c] = 1;
	return (tab[k][c] = c1 * v + s / v + f(k + 1, c) - s / (2. * m));
}

int main()
{
	int i;

	while (scanf("%lf %d", &m0, &n) == 2) {
		for (i = 0; i < n; i++)
			scanf("%lf", &len[i]);

		memset(got, 0, sizeof(got));
		printf("%.4f\n", f(0, 0));
	}

	return 0;
}
