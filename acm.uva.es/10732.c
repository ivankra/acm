#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define EPS 1e-15

double x[16384];
int n, n_pos;

int find_gt(int a, int b, double t)
{
	int c;

	for (t += EPS; a < b;)
		if (x[c = (a + b) >> 1] < t)
			a = c + 1;
		else
			b = c;

	return (x[b] > t) ? b : -1;
}

int find_lt(int a, int b, double t)
{
	int c;

	for (t -= EPS; a < b;)
		if (x[c = (a + b + 1) >> 1] < t)
			a = c;
		else
			b = c - 1;

	return (x[a] < t) ? a : -1;
}

int count(int a)
{
	int i, r, t, u;

	if (fabs(x[a]) < EPS) {
		i = find_gt(0, n - 1, 0.);
		return (i < 0) ? 0 : (n - i);
	}

	r = 0;

	t = find_gt(0, n - 1, -x[a]);
	if (t >= 0) {
		if (x[a] > 0) {
			u = find_lt(t, n - 1, 1. / x[a]);
			if (u >= 0) r += u - t + 1;
		} else {
			u = find_gt(t, n - 1, 1. / x[a]);
			if (u >= 0) r += n - u;
		}
	}

	t = find_lt(0, n - 1, -x[a]);
	if (t >= 0) {
		if (x[a] > 0) {
			u = find_gt(0, t, 1. / x[a]);
			if (u >= 0) r += t - u + 1;
		} else {
			u = find_lt(0, t, 1. / x[a]);
			if (u >= 0) r += u + 1;
		}
	}

	return r;
}

int cmp(const void *p, const void *q)
{
	return (*(double *)p > *(double *)q) ? 1 : -1;
}

int main()
{
	int i, r, t;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		for (i = 0; i < n; i++)
			scanf("%lf", &x[i]);

		qsort(x, n, sizeof(x[0]), &cmp);

		for (r = 0, i = 0; i < n; i++)
			r += count(i);

		for (i = 0; i < n; i++)
			if ((EPS < x[i] && x[i] < (1. - EPS)) ||
			    (x[i] < (-1. - EPS)))
				r--;

		assert(r >= 0 && (r % 2) == 0);

		printf("Case %d: %d\n", t, r / 2);
	}

	return 0;
}
