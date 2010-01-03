#include <stdio.h>
#include <math.h>
#define EPS 1e-9

double pi;

double sol(double a, double b, double c)
{
	double A = ((b*b+c*c-a*a)/(2*b*c));
	double B = ((a*a+c*c-b*b)/(2*a*c));
	if (A > EPS && B > EPS) {
		A /= sqrt(1 - A * A);
		B /= sqrt(1 - B * B);
		return c / (1 + A + B);
	} else if (A > EPS) {
		A /= sqrt(1 - A * A);
		return c / (1 + A);
	} else if (B > EPS) {
		B /= sqrt(1 - B * B);
		return c / (1 + B);
	} else {
		return c;
	}
}

double solve(double a, double b, double c)
{
	double r = sol(a,b,c); r >?= sol(a,c,b); r >?= sol(b,a,c);
	r >?= sol(b,c,a); r >?= sol(c,a,b); r >?= sol(c,b,a);
	return r*r;
}

int main()
{
	double a, b, c;
	int t;
	pi = 2. * acos(0.);
	for (scanf("%d", &t); t-- > 0 && scanf("%lf %lf %lf", &a, &b, &c) == 3;)
		printf("%.6f\n", solve(a,b,c));
	return 0;
}
