#include <stdio.h>
#include <stdlib.h>

long double a[65536];
int n;

int cmp(const void *p, const void *q)
{
	return ((*(long double *)p - *(long double *)q) > 0.) ? 1 : -1;
}

long double solve()
{
	long double c, t, s;
	int i, k, r;

	qsort(a, n, sizeof(a[0]), &cmp);

	for (c = 1., r = 0, k = 0; (r + 2) < n; r += 2, k++)
		c *= (r + 2.L) * (r + 1.L) / ((k + 1.L) * (r + 1.L - k) * 4.L);

	if (r < (n - 1)) {
		c *= (r + 1.L) / (long double)((r + 1.L - k) * 2.L);
		r++;
	}

	for (s = 0., i = k, t = c; i >= 0; i--) {
		s += t * a[i];
		t *= i / (long double)(r - i + 1.L);
	}

	t = (c * (r - k)) / (long double)(k + 1.L);
	for (i = k + 1; i <= r; i++) {
		s += t * a[i];
		t *= (r - i) / (long double)(i + 1.L);
	}

	return s;
}

int main()
{
	int i, c, t;

	for (scanf("%d", &t), c = 1; c <= t && scanf("%d", &n) == 1; c++) {
		for (i = 0; i < n; i++)
			scanf("%Lf", &a[i]);

		printf("Case #%d: %.3Lf\n", c, solve());
	}

	return 0;
}
