#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SQ(x) ((x)*(x))

int main()
{
	static double x1, y1, x2, y2, x3, y3;
	static double a2, b2, c2, s, l, pi;

	pi = 2. * acos(0.);

	while (scanf("%lf %lf %lf %lf %lf %lf",&x1,&y1,&x2,&y2,&x3,&y3) == 6) {
		a2 = SQ(x3 - x2) + SQ(y3 - y2);
		b2 = SQ(x3 - x1) + SQ(y3 - y1);
		c2 = SQ(x2 - x1) + SQ(y2 - y1);

		s = b2 + c2 - a2;
		s = 1. - (SQ(s) / (4. * b2 * c2));

		l = sqrt(a2 / s) * pi;

		printf("%.2f\n", l);
	}

	return 0;
}
