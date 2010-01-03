#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int m, n;
double dist[64][64];

int match(double maxd, int maxf)
{
	static int adj[64][64], dm[64], tn[64], tm[64];
	static int p[64], s[1024], f;
	int i, j, k, t;

	maxd += 1e-9;

	for (i = 0; i < m; i++)
		dm[i] = 0, tm[i] = -1;

	for (i = 0; i < n; i++)
		tn[i] = -1;

	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			if (dist[i][j] < maxd) adj[i][dm[i]++] = j;

	for (f = 0; f < maxf; f++) {
		for (t = 0, i = 0; i < m; i++)
			if (tm[i] < 0)
				p[s[t++] = i] = i;
			else
				p[i] = -1;

		while (t > 0) {
			i = s[--t];
			for (j = 0; j < dm[i]; j++) {
				k = adj[i][j];
				if (tn[k] < 0)
					goto found;

				if (p[tn[k]] >= 0)
					continue;

				p[s[t++] = tn[k]] = i;
			}
		}

		break;

found:		for(;;) {
			tn[k] = i;
			j = tm[i];
			tm[i] = k;
			k = j;
			if (p[i] == i) break;
			i = p[i];
		}
	}

	return f;
}

int cmp(const void *p, const void *q)
{
	return (*(double *)p > *(double *)q) ? 1 : -1;
}

double solve()
{
	static double d[4096], mx[64], my[64], nx[64], ny[64];
	int i, j, f, t;

	scanf("%d %d %d", &m, &n, &f);
	f = m - f;

	for (i = 0; i < m; i++)
		scanf("%lf %lf", &mx[i], &my[i]);

	for (i = 0; i < n; i++)
		scanf("%lf %lf", &nx[i], &ny[i]);

	if (m < 1 || f <= 0)
		return 0;

	if (n < 1 || m < f || n < f)
		return -1;

	for (i = 0, t = 0; i < m; i++)
		for (j = 0; j < n; j++) {
			dist[i][j] = ((mx[i] - nx[j]) * (mx[i] - nx[j]) +
				      (my[i] - ny[j]) * (my[i] - ny[j]));
			d[t++] = dist[i][j];
		}

	qsort(d, t, sizeof(d[0]), &cmp);

	if (match(d[t - 1], f) < f)
		return -1;

	for (i = 0, j = t - 1; (d[j] - d[i]) > 1e-5;)
		if (match(d[t = (i + j) >> 1], f) >= f)
			j = t;
		else
			i = t + 1;

	return sqrt(d[j]);
}

int main()
{
	int c, t;
	double r;

	for (scanf("%d", &t), c = 1; c <= t; c++) {
		printf("Case #%d:\n", c);
		if ((r = solve()) < 0)
			printf("Too bad.\n\n");
		else
			printf("%.3f\n\n", r);
	}

	return 0;
}
