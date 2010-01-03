#include <stdio.h>

long double a[32][32];
int n;

long double xabs(long double x)
{
	return (x < 0) ? -x : x;
}

long double solve()
{
	int i, j, k;
	long double r, t;

	for (r = 1., i = 0; i < n; i++) {
		for (k = j = i; j < n; j++)
			if (xabs(a[j][i]) > xabs(a[k][i])) k = j;

		if (xabs(a[k][i]) < 1e-8)
			return 0.;

		if (k != i) {
			for (j = i; j < n; j++) {
				t = a[k][j];
				a[k][j] = a[i][j];
				a[i][j] = t;
			}
			r = -r;
		}

		r *= a[i][i];

		for (k = i + 1; k < n; k++) {
			t = a[k][i] / a[i][i];
			a[k][i] = 0.;
			for (j = i + 1; j < n; j++)
				a[k][j] -= t * a[i][j];
		}
	}

	return r;
}

int main()
{
	int i, j;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				scanf("%Lf", &a[i][j]);
		printf("%.0Lf\n", solve());
	}
	printf("*\n");

	return 0;
}
