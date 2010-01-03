#include <stdio.h>
#include <math.h>

int main()
{
	double a, b, c, r;

	while (scanf("%lf %lf %lf", &a, &b, &c) == 3) {
		if (a < 0) a = -a;
		if (b < 0) b = -b;
		if (c < 0) c = -c;

		if (a < 1e-6 || b < 1e-6 || c < 1e-6 || (a + b + c) < 1e-6) {
			r = 0;
		} else {
			r = (a + b + c) * (-a + b + c) * (a - b + c) * (a + b - c);

			if (r <= 1e-6) {
				r = 0.0;
			} else {
				r = sqrt(r);
				r /= 2. * (a + b + c);
			}
		}

		if (r < 0) r = 0.0;

		printf("The radius of the round table is: %.3f\n", r);
	}

	return 0;
}
