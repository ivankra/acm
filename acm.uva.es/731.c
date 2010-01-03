#include <stdio.h>
#include <math.h>

long double f(long double x)
{
	long double k, s;
	int i;

	for (s = 0, k = 1, i = 1; i < 10000; i++, k += 1.)
		s += 1. / (k * (k + 1.) * (k + 2.) * (k + 3.) * (k + 4.) * (k + x));

	return (1. - x) * ((2. - x) * ((3. - x) * ((4. - x) * s + 1. / 96.) + 1. / 18.) + 0.25) + 1.;
}

int main()
{
	int i;

	for (i = 0; i <= 3000; i++)
		printf("%3d.%d0%17.12Lf\n", i / 10, i % 10, f(i * .1));

	return 0;
}
