// ICPC Finals 2003 - Problem I - The Solar System
#include <cstdio>
#include <cmath>

double PI = 2 * acos(0.0);
double a, b, c, area;

double sqr(double x) { return x * x; }
double cube(double x) { return x * x * x; }

double computeSweptArea(double phi)
{
	double x0 = a * cos(phi);
	double y0 = b * sin(phi);

	double t = acos(x0 / a);
	double A = a*b*(t-sin(t)*cos(t))/2 + (x0-c)*fabs(y0)/2;

	if (y0 > 0) {
		return A;
	} else {
		return area - A;
	}
}

int main()
{
	int a1, b1, t1, a2, b2, t;
	for (int cs = 1; ; cs++) {
		int i = scanf("%d %d %d %d %d %d", &a1, &b1, &t1, &a2, &b2, &t);
		if (i != 6) break;
		if ((a1|b1|t1|a2|b2|t) == 0) break;

		a = a2;
		b = b2;
		c = sqrt(a*a - b*b);
		area = PI * a * b;

		double period = sqrt(sqr(t1) * cube(a2) / cube(a1));
		double swept = fmod(t * area / period, area);

		double left = 0, right = 2*PI, phi;
		for (int k = 0; k < 30; k++) {
			phi = (left + right) / 2;
			if (computeSweptArea(phi) > swept)
				right = phi;
			else
				left = phi;
		}

		phi = (left + right) / 2;
		printf("Solar System %d: %.3f %.3f\n", cs, a*cos(phi), b*sin(phi));
	}
}
