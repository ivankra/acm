#include <stdio.h>
#include <math.h>

int main()
{
	double a, b, c, r;
	int i, s, n;

	a = 1.2;
	b = 1.4;

	for (i = 0; i < 100; i++) {
		r = (a + b) / 2;
		c = r * r * r * r * (r - 1) - 1;

		if (c < 0.)
			a = r;
		else
			b = r;
	}

	r = (a + b) / 2;
	a = log10(r);

	while (scanf("%d %d", &s, &n) == 2) {
		c = (n - 1) * a + log10((double)s) + 1 + 1e-15;
		if (c >= 10.)
			printf("%.0f\n", floor(c));
		else
			printf("%.0f\n", floor(s * pow(r, n - 1)));
	}

	return 0;
}
