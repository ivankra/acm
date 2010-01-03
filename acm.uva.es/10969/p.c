#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define EPS 1e-10

struct { double r, x, y; } C[128];
int n;
double pi;

double sq(double x) { return x*x; }
int cmp(const void *p, const void *q) { return (*(double *)p > *(double *)q) ? 1 : -1; }

/* Returns length of visible boundary of s-th disk */
double visible(int s)
{
	double a[256], d, u, v, x, y, r;
	int i, j, k, t;

	if (C[s].r < EPS)
		return 0.;

	/* Find the points of intersection of s-th disk with disks above it */
	k = 0;
	for (t = s + 1; t < n; t++) {
		d = sq(C[s].x - C[t].x) + sq(C[s].y - C[t].y);
		if (d > sq(C[s].r + C[t].r) - EPS)
			/* disks intersect at less than 2 points */
			continue;

		if (d < sq(C[s].r - C[t].r) + EPS) {
			/* some disk is completely contained in the other disk,
			   or the disks have the same coordinates and radii */
			if (C[s].r < C[t].r+EPS)
				/* s-th disk is completely covered by t-th disk */
				return 0.;
			continue;
		}

		/* the circumferences of s-th and t-th disk intersect at
		   two distinct points */

		assert(d > EPS);

		u = (sq(C[s].r) - sq(C[t].r) + d) / (2. * C[s].r * sqrt(d));
		assert(-1.-EPS < u && u < 1.+EPS);
		u = acos(u);
		assert(-EPS < u && u < pi+EPS);

		v = atan2(C[t].y - C[s].y, C[t].x - C[s].x);

		/* remember the polar angle of points of intersections
		   (relative to s-th disk) */
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
	   sum the lengths of visible parts */
	r = 0.;
	for (i = 0; i < k; i++) {
		if ((a[i+1] - a[i]) < EPS) continue;

		/* I assume that the arc [a[i]..a[i+1]] is not
		   visible if its midpoint is in some disk above it */
		u = (a[i] + a[i+1]) / 2.;
		x = C[s].x + C[s].r * cos(u);
		y = C[s].y + C[s].r * sin(u);
		for (j = s + 1; j < n; j++)
			if ((sq(C[j].x-x) + sq(C[j].y-y)) < sq(C[j].r)+EPS) break;
		if (j < n) continue;

		r += (a[i+1] - a[i]) * C[s].r;
	}

	return r;
}

int main()
{
	int i, j, t;
	double r;

	pi = 2. * acos(0.);

	i = scanf("%d", &t);
	assert(i == 1);

	while (t-- > 0) {
		i = scanf("%d", &n);
		assert(i == 1 && 0 <= n && n <= 100);

		for (i = 0; i < n; i++) {
			j = scanf("%lf %lf %lf", &C[i].r, &C[i].x, &C[i].y);
			assert(j == 3);
			if (C[i].r < EPS) C[i].r = 0.;
		}

		for (r = 0., i = 0; i < n; i++)
			r += visible(i);

		printf("%.3f\n", r);
	}

	return 0;
}
