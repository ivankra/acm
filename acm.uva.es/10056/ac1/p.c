#include <stdio.h>
#include <math.h>

int main()
{
	double p, r;
	int k, m, n, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %lf %d", &n, &p, &m) == 3;){
		for (k = 0, r = 0.; k < 500; k++)
			r += pow(1. - p, n * k + m - 1) * p;

		printf("%.4f\n", r);
	}

	return 0;
}
