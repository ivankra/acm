#include <stdio.h>
#include <math.h>

int main()
{
	int t, n;
	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n);)
		if (n <= 1)
			printf("0.000\n");
		else
			printf("%.3f\n", n*n+(sqrt(2.)-1.)*(n-2)*(n-2));
	return 0;
}
