#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int int_sqrt(int n)
{
	register int x, y;

	for (x = n; x != 0; x = y)
		if ((y = ((x + (n / x)) >> 1)) >= x) return x;

	return 0;
}

int main()
{
	int i, m, n;
	double phi;

	while (scanf("%d", &n) > 0 && n > 0) {
		phi = n;

		m = int_sqrt(n) + 2;
		for (i = 2; n > 1 && i <= m; i = (i == 2) ? 3 : (i + 1)) {
			if ((n % i) == 0) {
				phi *= 1. - (1. / (double)i);
				do { n /= i; } while ((n % i) == 0);
				m = int_sqrt(n) + 2;
			}
		}

		if (n > 1)
			phi *= 1. - (1. / (double)n);

		if (abs(phi - ceil(phi)) < abs(phi - floor(phi)))
			printf("%d\n", (int)ceil(phi));
		else
			printf("%d\n", (int)floor(phi));
	}

	return 0;
}
