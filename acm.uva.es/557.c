#include <stdio.h>
#include <math.h>

double lgamma(double);

int main()
{
	int t, n;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;)
		printf("%.4f\n",
			1. - exp(lgamma(n-1) - 2.*lgamma(n/2.) - (n-2)*log(2.)));

	return 0;
}
