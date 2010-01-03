#include <stdio.h>
#include <math.h>

int main()
{
	double a, c;

	a = acos(0.) / 90.;
	c = sin(108. * a) / sin(63. * a);

	while (scanf("%lf", &a) == 1)
		printf("%.10f\n", c * a);

	return 0;
}
