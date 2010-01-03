#include <stdio.h>
#include <math.h>

int main()
{
	int d, v;
	double r, pi;

	pi = 2. * acos(0.);

	while (scanf("%d %d", &d, &v) == 2 && (d | v) != 0) {
		r = (double)d * (double)d * (double)d - 6. * (double)v / pi;
		r = pow(r, 1. / 3.);
		printf("%.3f\n", r);
	}

	return 0;
}
