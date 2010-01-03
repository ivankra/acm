#include <stdio.h>
#include <math.h>

#define EPS 1e-9

double x[3], y[3], a, xmin, xmax, ymin, ymax;

int inside(double cx, double cy)
{
	double t;

	if (cx < (xmin - EPS)) return 0;
	if (cx > (xmax + EPS)) return 0;
	if (cy < (ymin - EPS)) return 0;
	if (cy > (ymax + EPS)) return 0;

	t = fabs((x[1] - cx) * (y[2] - cy) - (x[2] - cx) * (y[1] - cy));
	t += fabs((x[0] - cx) * (y[2] - cy) - (x[2] - cx) * (y[0] - cy));
	t += fabs((x[0] - cx) * (y[1] - cy) - (x[1] - cx) * (y[0] - cy));

	return (fabs(t - a) < EPS) ? 1 : 0;
}

int main()
{
	int i, j, k, xl, yl, xh, yh;

	for (;;) {
		for (i = 0; i < 3; i++)
			scanf("%lf %lf", &x[i], &y[i]);

		for (i = 0; i < 3; i++)
			if (fabs(x[i]) > 1e-15 || fabs(y[i]) > 1e-15) break;
		if (i == 3) break;

		a = fabs((x[1] - x[0]) * (y[2] - y[0]) - (x[2] - x[0]) * (y[1] - y[0]));

		xmin = xmax = x[0];
		ymin = ymax = y[0];

		for (i = 1; i < 3; i++) {
			if (x[i] < xmin) xmin = x[i];
			if (x[i] > xmax) xmax = x[i];
			if (y[i] < ymin) ymin = y[i];
			if (y[i] > ymax) ymax = y[i];
		}

		xl = floor(xmin - EPS);
		yl = floor(ymin - EPS);
		xh = ceil(xmax + EPS);
		yh = ceil(ymax + EPS);

		if (xl < 1) xl = 1;
		if (yl < 1) yl = 1;
		if (xh > 99) xh = 99;
		if (yh > 99) yh = 99;

		for (i = xl, k = 0; i <= xh; i++)
			for (j = yl; j <= yh; j++)
				k += inside(i, j);

		printf("%4d\n", k);
	}

	return 0;
}
