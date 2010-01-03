#include <stdio.h>
#include <string.h>
#include <math.h>

static int got[65536], x[16], y[16], n, id;
static float d[16][16], tab[65536];

static float f(int m)
{
	int s, i;
	float t;

	if (got[m] == id) return tab[m];
	got[m] = id;

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
	int i, j;

	for (id = 1; scanf("%d", &n) == 1 && n > 0; id++) {
		n *= 2;
		for (i = 0; i < n; i++)
			scanf(" %*s %d %d", &x[i], &y[i]);

		for (i = 0; i < n; i++) {
			d[i][i] = 0.;
			for (j = i + 1; j < n; j++) {
				d[j][i] = d[i][j] =
					(float)sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
			}
		}

		printf("Case %d: %.2f\n", id, (double)f(0));
	}

	return 0;
}
