#include <stdio.h>
#include <math.h>

double hypot(double, double);

int main()
{
	double x1, y1, x2, y2, d, a;

	while (scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2) == 4) {
		d = .5 * hypot(x1 - x2, y1 - y2);
		a = atan2(y2 - y1, x2 - x1);
		printf("%.10f %.10f %.10f %.10f\n",
			(x1 + x2) / 2. - d * sin(a), (y1 + y2) / 2. + d * cos(a),
			(x1 + x2) / 2. + d * sin(a), (y1 + y2) / 2. - d * cos(a));
	}

	return 0;
}
