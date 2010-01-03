/* uva 688; returns area of union of squares (generalizable to rectangles.)
   sweep-line algorithm, O(n^2). */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-9

typedef struct { double x, y, r; } sqr_t;
sqr_t sq[1024];
int n, m;

int dcmp(const void *p, const void *q)
{
	return (*(double *)p > *(double *)q) ? 1 : -1;
}

int scmp(const void *p, const void *q)
{
	return (((sqr_t *)p)->y > ((sqr_t *)q)->y) ? 1 : -1;
}

double solve()
{
	static double sw[2048], area, up;
	int i, j;

	qsort(sq, n, sizeof(sq[0]), &scmp);

	for (m = 0, i = 0; i < n; i++) {
		sw[m++] = sq[i].x;
		sw[m++] = sq[i].x + sq[i].r;
	}
	qsort(sw, m, sizeof(sw[0]), &dcmp);

	for (area = 0., i = 1; i < m; i++) {
		if ((sw[i] - sw[i - 1]) < EPS)
			continue;

		for (up = -1. / 0., j = 0; j < n; j++) {
			if (sq[j].x < (sw[i - 1] + EPS) &&
			    (sq[j].x + sq[j].r) < (sw[i - 1] + EPS))
				continue;

			if (sq[j].x > (sw[i] - EPS) &&
			    (sq[j].x + sq[j].r) > (sw[i] - EPS))
				continue;

			if (sq[j].y < (up + EPS)) {				
				if ((sq[j].y + sq[j].r) > up) {
					area += (sq[j].y + sq[j].r - up) * (sw[i] - sw[i - 1]);
					up = sq[j].y + sq[j].r;
				}
			} else {
				area += sq[j].r * (sw[i] - sw[i - 1]);
				up = sq[j].y + sq[j].r;
			}
		}
	}

	return area;
}

int main()
{
	int i, t;

	for (t = 1; scanf("%d", &n) == 1 && n != 0; t++) {
		for (i = 0; i < n; i++) {
			scanf("%lf %lf %lf", &sq[i].x, &sq[i].y, &sq[i].r);
			sq[i].x -= sq[i].r;
			sq[i].y -= sq[i].r;
			sq[i].r *= 2;
		}
		printf("%d %.2f\n", t, solve());
	}

	return 0;
}
