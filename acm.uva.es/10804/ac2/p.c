#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int m, n;
double dist[64][64];

int match(double maxd, int maxf)
{
	static int adj[64][64], dm[64], tn[64], tm[64];
	static int p[64], s[64], f, found, st;
	int i, j, k, t;

	for (i = 0; i < m; i++)
		dm[i] = 0, tm[i] = -1;

	for (i = 0; i < n; i++)
		tn[i] = -1;

	maxd += 1e-9;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			if (dist[i][j] < maxd) adj[i][dm[i]++] = j;

	if (maxf == 0)
		return 0;

	for (f = 0;;) {
		for (i = 0; i < m; i++)
			p[i] = (tm[i] < 0) ? i : -1;

		for (found = 0, st = 0; st < m; st++) {
			if (tm[st] >= 0) continue;

			for (s[0] = st, t = 1; t > 0;) {
				i = s[--t];

				for (j = 0; j < dm[i]; j++) {
					k = adj[i][j];
					if (tn[k] < 0) {
						for (;; i = p[i]) {
							tn[k] = i;
							j = tm[i];
							tm[i] = k;
							if ((k = j) < 0) break;
						}

						found = 1;
						if (++f >= maxf) return maxf;
						goto done;
					}

					if (p[tn[k]] >= 0)
						continue;

					p[s[t++] = tn[k]] = i;
				}
			}
done: ;
		}

		if (found == 0) break;
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
