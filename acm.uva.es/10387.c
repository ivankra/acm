#include <stdio.h>
#include <math.h>

int main()
{
	double a, b, s, m, n, pi = 2. * acos(0.);
	while (scanf("%lf%lf%lf%lf%lf", &a, &b, &s, &m, &n) == 5 && a > .1)
		printf("%.2f %.2f\n", atan(n * b / (m * a)) * 180. / pi,
		       sqrt(n * n * b * b + m * m * a * a) / s);
	return 0;
}
