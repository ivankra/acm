#include <cstdio>
#include <cmath>
#define EPS 1e-9

double PI = 2*acos(0.);

double f(double a) {
	if (a > PI) a = 2*PI-a;
	return PI - a - sin(a);
}

int main()
{
	int cs, n;
	double p[128], s[128], r;

	for (int cs = 1; scanf("%lf %d", &r, &n) == 2 && n > 0; cs++) {
		int m = (n+1)/2;
		double d=2*PI/n;

		printf("Set %d:\n%d\n", cs, m);

		p[0] = s[0] = 0;
		for (int i = 1; i <= m; i++) {
			p[i] = f(d*(m+i-1+(n%2==0 ? 1 : 0)));
			for (int j = 1; i-j > 0; j++)
				p[i] -= (j+1)*p[i-j];

			s[i] = 0;
			for (int j = 0; i-j > 0; j++)
				s[i] += (j+1)*p[i-j];

			printf("%.4f %.4f\n", s[i]*n*r*r, p[i]*n*r*r);
		}
	}

	return 0;
}
