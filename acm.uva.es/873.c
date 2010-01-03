#include <stdio.h>
#include <math.h>

int main()
{
	double i, m, n;
	int t;

	for (scanf("%d", &t); t-- > 0 && scanf("%lf %lf %lf", &m, &i, &n) == 3;) {
		if (fabs(i) < 1e-10) {
			printf("%.2f\n", m / n);
		} else {
			i = i / 1200.;
			printf("%.2f\n", m * i * (1. + 1. / (pow(1. + i, n) - 1.)));
		}

		if (t > 0)
			printf("\n");
	}

	return 0;
}
