#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/* O(n^3) algorithm */

#define EPS 1e-10

struct { double r, x, y; } C[128];
int n;
double pi;

double sq(double x) { return x * x; }
int cmp(const void *p, const void *q) { return (*(double *)p > *(double *)q) ? 1 : -1; }

/* Returns length of visible boundary of s-th disk */
double visible(int s)
{
	double a[256], d, u, v, x, y, r;
	int i, j, k, t;

	/* Find the points of intersection of s-th disk with disks above it */
	k = 0;
	for (t = s + 1; t < n; t++) {
		d = sq(C[s].x - C[t].x) + sq(C[s].y - C[t].y);
		if (d > sq(C[s].r + C[t].r) - EPS) continue;

		if (d < sq(C[s].r - C[t].r) + EPS) {
			if (C[s].r < C[t].r+EPS) return 0.;
			continue;
		}

		u = (sq(C[s].r) - sq(C[t].r) + d) / (2. * C[s].r * sqrt(d));
		u = acos(u);	/* u \in [0,pi] */

		v = atan2(C[t].y - C[s].y, C[t].x - C[s].x);

		a[k++] = v + u;
		a[k++] = v - u;
	}

	if (k == 0)
		return 2 * pi * C[s].r;

	/* Normalize and sort the angles */
	for (i = 0; i < k; i++) {
		while (a[i] < 0) a[i] += 2*pi;
		while (a[i] > 2*pi) a[i] -= 2*pi;
	}
	qsort(a, k, sizeof(a[0]), &cmp);
	a[k] = a[0] + 2*pi;

	/* For each angular interval, check if it's visible;
	   sum the length of visible parts */
	r = 0.;
	for (i = 0; i < k; i++) {
		if ((a[i+1] - a[i]) < EPS) continue;

		u = (a[i] + a[i+1]) / 2.;

		x = C[s].x + C[s].r * cos(u);
		y = C[s].y + C[s].r * sin(u);

		for (j = s + 1; j < n; j++)
			if ((sq(C[j].x-x) + sq(C[j].y-y)) < C[j].r*C[j].r+EPS) break;

		if (j >= n)
			r += (a[i+1] - a[i]) * C[s].r;
	}

	return r;
}

int main()
{
	int i, j, t;
	double r;

	pi = 2. * acos(0.);

	for (scanf("%d", &t); t >= 0 && scanf("%d", &n) == 1; t--) {
		assert(0 <= n && n <= 100);
		for (i = 0; i < n; i++) {
			j = scanf("%lf %lf %lf", &C[i].r, &C[i].x, &C[i].y);
			assert(j == 3 && C[i].r > -EPS);
		}

		for (r = 0., i = 0; i < n; i++)
			r += visible(i);

		printf("%.3f\n", r);
	}
	assert(t == 0);

	return 0;
}
