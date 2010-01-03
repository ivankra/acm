#include <stdio.h>
#include <math.h>

int main()
{
	double p, r;
	int m, n, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %lf %d", &n, &p, &m) == 3;){
		if (p < 10e-6)
			r = 0.;
		else
			r = pow(1. - p, m - 1) * p / (1. - pow(1. - p, n));

		printf("%.4f\n", r);
	}

	return 0;
}
