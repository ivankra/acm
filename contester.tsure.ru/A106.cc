#include <cstdio>
#include <cmath>

int main()
{
	double a, r, pi=2*acos(0.0);
	scanf("%lf %lf", &a, &r); a /= 2;
	if (r < a+1e-9)
		printf("%.3f\n", pi*r*r);
	else if (2*a*a < r*r+1e-9)
		printf("%.3f\n", 4*a*a);
	else
		printf("%.3f\n", r*r*(pi-4*acos(a/r)) + 4*a*sqrt(r*r-a*a));
}
