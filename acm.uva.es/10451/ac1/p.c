#include <stdio.h>
#include <math.h>

int main()
{
	double a, r_out_2, r_in_2, pi;
	int t, n;

	pi = 2. * acos(0.);

	for (t = 1; scanf("%d%lf", &n, &a) == 2 && n >= 3; t++) {
		r_out_2 = 2. * a / ((double)n * sin(2. * pi / (double)n));
		r_in_2 = cos(pi / (double)n);
		r_in_2 = r_out_2 * r_in_2 * r_in_2;

		printf("Case %d: %.5f %.5f\n",
		       t, r_out_2 * pi - a, a - r_in_2 * pi);
	}

	return 0;
}
