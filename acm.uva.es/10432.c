#include <stdio.h>
#include <math.h>

int main()
{
	double r, n, a, p;

	p = 4. * acos(0.);

	while (scanf("%lf%lf", &r, &n) == 2) {
		a = n * r * r * sin(p / n) / 2.;
		printf("%.3f\n", a);
	}

	return 0;
}
