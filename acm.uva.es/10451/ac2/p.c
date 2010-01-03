#include <stdio.h>
#include <math.h>

int main()
{
	double a, r_out_2, r_in_2, tanx, cotx, pi;
	int t, n;

	pi = 2. * acos(0.);

	for (t = 1; scanf("%d%lf", &n, &a) == 2 && n >= 3; t++) {
		tanx = tan(pi / (double)n);
		cotx = 1. / tanx;

		r_out_2 = (a / n) * (cotx + tanx);
		r_in_2 = (a / n) * cotx;

		printf("Case %d: %.5f %.5f\n",
		       t, r_out_2 * pi - a, a - r_in_2 * pi);
	}

	return 0;
}
