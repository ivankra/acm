#include <stdio.h>
#include <math.h>

double cf;

double f(double x)
{
	return exp(-x * x / 2.) / cf;
}

double F(double x)
{
	double r, t = 1. / (1. + .2316419 * fabs(x));
	r = (1.330274429 * t - 1.821255978) * t + 1.781477937;
	r = ((r * t - .356563782) * t + .319381530) * t;
	return f(x) * r;
}

int main()
{
	double m, d, z;
	int i, n, q, t;

	cf = sqrt(4 * acos(0));
	for (t = 1; scanf("%d", &n) == 1; t++) {
		if (t > 1) printf("\n");
		printf("Data Set #%d\n", t);

		for (i = 0, m = 0., d = 0.; i < n && scanf("%lf", &z) == 1; i++) {
			m += z;
			d += z * z;
		}			

		d = sqrt((d - m * m / (double)n) / (double)(n - 1));
		m /= (double)n;

		printf("Mean = %.4f\n", m);
		printf("Standard Deviation = %.4f\n", d);

		scanf("%d", &q);
		while (q-- > 0 && scanf("%lf", &z) == 1) {
			z = (z - m) / d;
			printf("P(z) = %.4f, Q(z) = %.4f, T = %.4f\n", 1. - F(z), F(z), n * F(z));
		}
	}

	return 0;
}
