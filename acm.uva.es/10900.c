#include <stdio.h>

double t;

double f(double m, int n)
{
	double a, q;

	if (n < 1) return m;

	a = f(2 * m, n - 1);
	if (a < m) return m;

	q = m / a;
	if (t > (q - 1e-9))
		return a * (t + 1.) / 2.;
	else
		return m * (q - t) / (1. - t) + (1. - (q - t) / (1. - t)) * a * (q + 1.) / 2.;
}

int main()
{
	int n;

	while (scanf("%d %lf", &n, &t) == 2 && n > 0)
		printf("%.3f\n", f(1, n));

	return 0;
}
