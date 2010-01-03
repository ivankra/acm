#include <stdio.h>

int main()
{
	static double a[100000];
	int i, n;

	for (a[0] = 0, i = 1; i < 100000; i++)
		a[i] = a[i - 1] + (1. / (2. * i));

	printf("# Cards Overhang\n");
	while (scanf("%d", &n) == 1)
		printf("%5d%10.3f\n", n, a[n]);

	return 0;
}
