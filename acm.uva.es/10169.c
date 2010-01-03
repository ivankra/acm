#include <stdio.h>
#include <math.h>

double lgamma(double);

int main()
{
	static double r[1048576], t;
	int i, n;

	for (r[0] = 0., i = 1; i <= 1000000; i++)
		r[i] = r[i - 1] + (1 - r[i - 1]) / ((double)i * (double)(i+1));

	while (scanf("%d", &n) == 1) {
		t = (2 * lgamma(n + 1.) + log(n + 1.)) / log(10.);
		printf("%.6f %.0f\n", r[n], floor(t + 1e-15));
	}

	return 0;
}
