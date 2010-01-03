#include <stdio.h>
#include <math.h>

int main()
{
	static double k1, k2, k3, a, b, c, r, r2;

	k3 = 4. - sqrt(3.) - (acos(0.) * 4. / 3.);
	k2 = sqrt(3.) * 2. + (acos(0.) * 2. / 3.) - 4.;
	k1 = 1 - k2 - k3;

	while (scanf("%lf", &r) == 1) {
		r2 = r * r;
		a = k1 * r2;
		b = k2 * r2;
		c = k3 * r2;
		printf("%.3f %.3f %.3f\n", a, b, c);
	}

	return 0;
}
