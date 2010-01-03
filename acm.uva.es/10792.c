#include <stdio.h>
#include <math.h>

int main()
{
	int n, t;
	double r, d, h, a;

	for (scanf("%d", &n), t = 1; t <= n; t++) {
		scanf("%lf %lf %lf", &r, &d, &h);
		a = asin(h / r - 1) - acos(1 - 2 * d * (2 * r - d) / (r * r));
		printf("Case %d: %.4f\n", t, r * (1 + sin(a)));
	}

	return 0;
}
