#include <stdio.h>

#define EQ(a, b) ((((a) > (b)) ? ((a) - (b)) : ((b) - (a))) < 10e-6)
#define PTEQ(a,b) (EQ(x[a], x[b]) && EQ(y[a], y[b]))

int main()
{
	static double x[4], y[4];
	int a, b, c;

	while (scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &x[0], &y[0], &x[1], &y[1], 
		     &x[2], &y[2], &x[3], &y[3]) == 8) {

		if (PTEQ(0, 2)) {
			b = 0;
			a = 1;
			c = 3;
		} else if (PTEQ(0, 3)) {
			b = 0;
			a = 1;
			c = 2;
		} else if (PTEQ(1, 2)) {
			b = 1;
			a = 0;
			c = 3;
		} else {
			b = 1;
			a = 0;
			c = 2;
		}

		printf("%.3f %.3f\n",
		       x[a] + x[c] - x[b],
		       y[a] + y[c] - y[b]);
	}

	return 0;
}
