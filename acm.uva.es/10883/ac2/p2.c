#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double a[65536];
int n;

int cmp(const void *p, const void *q)
{
	return (*(double *)p > *(double *)q) ? 1 : -1;
}

double solve()
{
	double c, t, s;
	int i, j, k, r;

	qsort(a, n, sizeof(a[0]), &cmp);

	for (c = 1., r = 0, k = 0; (r + 2) < n; r += 2, k++)
		c *= (r + 2.) * (r + 1.) / ((k + 1.) * (r + 1. - k) * 4.);

	if (r < (n - 1)) {
		c *= (r + 1.) / (double)((r + 1. - k) * 2.);
		r++;
	}

	if (r & 1) {
		for (s = 0., i = k, j = k + 1; i >= 0; i--, j++) {
			s += c * (a[i] + a[j]);
			c *= i / (double)(r - i + 1.);
		}
	} else {
		s = c * a[k];
		c *= k / (double)(r - k + 1.);
		for (i = k - 1, j = k + 1; i >= 0; i--, j++) {
			s += c * (a[i] + a[j]);
			c *= i / (double)(r - i + 1.);
		}
	}

	return s;
}

int main()
{
	int i, c, t;

	for (scanf("%d", &t), c = 1; c <= t && scanf("%d", &n) == 1; c++) {
		for (i = 0; i < n; i++)
			scanf("%lf", &a[i]);

		printf("Case #%d: %.3f\n", c, solve());
	}

	return 0;
}
