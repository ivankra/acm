#include <stdio.h>
#include <math.h>
#define EPS 1e-10

double heron(double a, double b, double c) {
	if (a+b<c+EPS || b+c<a+EPS || a+c<b+EPS) return 0;
	double p = (a+b+c)/2.0;
	return sqrt((p*(p-a)*(p-b)*(p-c)) >? 0);
}

int main()
{
	int T;
	double r1, r2, r3;
	for (scanf("%d", &T); T-- > 0 && scanf("%lf %lf %lf", &r1, &r2, &r3) == 3;) {
		double a = r2+r3, b = r1+r3, c = r1+r2;

		double A = (b*b+c*c-a*a)/(2*b*c);
		double B = (a*a+c*c-b*b)/(2*a*c);
		double C = (a*a+b*b-c*c)/(2*a*b);

		double s = heron(a,b,c);
		s -= 0.5*r1*r1*acos(A);
		s -= 0.5*r2*r2*acos(B);
		s -= 0.5*r3*r3*acos(C);

		printf("%.6f\n", s);
	}
	return 0;
}
