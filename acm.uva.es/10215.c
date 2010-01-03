#include <stdio.h>
#include <math.h>

int main()
{
	double w, l, t;

	while (scanf("%lf %lf", &l, &w) == 2) {
		t = (w + l - sqrt(w * w - w * l + l * l)) / 6.;
		printf("%.3f 0.000 %.3f\n",
		       t, (w < l) ? (w / 2.) : (l / 2.));
	}

	return 0;
}
