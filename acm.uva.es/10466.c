#include <stdio.h>
#include <math.h>

int main()
{
	int n, z, r, t;
	double a, x, y, d, pi;

	pi = 2. * acos(0.);

	while (scanf("%d %d", &n, &z) == 2) {
		x = y = 0.;

		while (n-- > 0) {
			scanf("%d %d", &r, &t);

			a = 2. * pi * (double)(z % t) / (double)t;

			x += (double)r * cos(a);
			y += (double)r * sin(a);
			d = sqrt(x * x + y * y);

			printf("%.4f", d);

			if (n > 0)
				printf(" ");
			else
				printf("\n");
		}
	}

	return 0;
}
