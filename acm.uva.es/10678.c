#include <stdio.h>
#include <math.h>

int main()
{
	int t, d, l;
	double pi;

	pi = 2. * acos(0.);

	for (scanf("%d", &t); t-- && scanf("%d %d", &d, &l) == 2;)
		printf("%.3f\n", pi * l * sqrt(l * l - d * d) / 4.);

	return 0;
}
