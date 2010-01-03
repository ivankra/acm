#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double lgamma(double);

double a[65536], l2;
int n;

double solve()
{
	double c, s;
	int i, j, k, r;

	r = n - 1;
	k = r >> 1;

	if (r & 1) {
		c = exp(lgamma(r + 1) - lgamma(k + 1) - lgamma(r - k + 1) - r * l2);
		for (s = 0., i = k, j = k + 1; i >= 0; i--, j++) {
			s += c * (a[i] + a[j]);
			c *= i / (double)(r - i + 1.);
		}
	} else {
		c = exp(lgamma(r + 1) - 2 * lgamma(k + 1) - r * l2);
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

	l2 = log(2.);

	for (scanf("%d", &t), c = 1; c <= t && scanf("%d", &n) == 1; c++) {
		for (i = 0; i < n; i++)
			scanf("%lf", &a[i]);

		printf("Case #%d: %.3f\n", c, solve());
	}

	return 0;
}
