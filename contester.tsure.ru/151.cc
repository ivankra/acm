#include <cstdio>
#include <cmath>

int main()
{
	double x, y, s, n;
	scanf("%lf %lf %lf %lf", &s, &n, &x, &y);

	double pi = 2*acos(0.0), phi = 2*pi/n;
	double d = hypot(y, x), a = fabs(atan2(y, x));
	while (a >= phi) a -= phi;
	x = d * cos(a);
	y = d * sin(a);

	double r = x + y * (1 - cos(phi)) / sin(phi);
	double z = (n*r*r*sin(phi)/2) / s;
	printf("%.0f\n", fabs(floor(z-1e-9)));
}
