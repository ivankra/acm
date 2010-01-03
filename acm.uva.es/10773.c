#include <stdio.h>
#include <math.h>

int main()
{
	int t, T;
	double d, u, v;
	for (scanf("%d", &T), t = 1; t <= T && scanf("%lf %lf %lf", &d, &v, &u) == 3; t++) {
		printf("Case %d: ", t);
		if (fabs(u) < 1e-9 || fabs(v) < 1e-9 || u < v+1e-9)
			printf("can't determine\n");
		else
			printf("%.3f\n", fabs(d/u - d/sqrt(u*u-v*v)));
	}
	return 0;
}
