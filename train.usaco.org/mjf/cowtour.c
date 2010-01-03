/*
ID: mjf28791
PROG: cowtour
LANG: C
*/
#include <stdio.h>
#include <string.h>

double hypot(double, double);

int c[256][256], n;
double d[256][256], a[256], x[256], y[256], m, r;

int main()
{
	int i, j, k;
	double t;

	freopen("cowtour.in", "r", stdin);
	freopen("cowtour.out", "w", stdout);

	scanf("%d", &n);

	for (i = 0; i < n; i++)
		scanf("%lf %lf", &x[i], &y[i]);

	memset(c, 0, sizeof(c));
	for (i = 0; i < n; i++)
		for (j = 0; j < n && (k = getchar()) != EOF;)
			if (k == '0' || k == '1') c[i][j++] = k - '0';

	for (i = 0; i < n; i++)
		c[i][i] = 1;

	for (i = 0; i < n; i++)
		for (j = i; j < n; j++)
			d[j][i] = d[i][j] = hypot(x[i] - x[j], y[i] - y[j]);

	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			if (c[i][k] == 0) continue;

			for (j = i + 1; j < n; j++) {
				if (c[k][j] && (c[i][j] == 0 ||
				     (d[i][k] + d[k][j]) < d[i][j])) {
					c[i][j] = c[j][i] = 1;
					d[i][j] = d[j][i] = d[i][k] + d[k][j];
				}
			}
		}
	}

	for (m = 0, i = 0; i < n; i++) {
		for (a[i] = 0, j = 0; j < n; j++)
			if (c[i][j] && d[i][j] > a[i]) a[i] = d[i][j];
		if (a[i] > m) m = a[i];
	}

	r = 1. / 0.;

	for (i = 0; r > m && i < n; i++) {
		for (j = 0; j < n; j++) {
			if (c[i][j]) continue;

			t = a[i] + d[i][j] + a[j];
			if (t < r) r = t;
		}
	}

	if (r < m) r = m;

	printf("%.6f\n", r);

	return 0;
}
