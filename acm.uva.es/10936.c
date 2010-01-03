#include <stdio.h>
#include <math.h>

int main()
{
	double x, y, t, d, a, a1, a2, a3, pi = 2 * acos(0.);
	int n;

	while (scanf("%d %lf %*s", &n, &x) >= 2 && n >= 3) {
		y = a = 0.; t = x;
		while (n-- > 1 && scanf("%lf %lf d %lf ' %lf \"", &d, &a1, &a2, &a3) == 4) {
			t += d;
			a += pi - (a1 + a2 / 60. + a3 / 3600.) * pi / 180.;
			x += d * cos(a);
			y += d * sin(a);
		}

		if (t < 1e-9 || (sqrt(x * x + y * y) / t) < 0.001)
			printf("Acceptable\n");
		else
			printf("Not acceptable\n");
	}

	return 0;
}
