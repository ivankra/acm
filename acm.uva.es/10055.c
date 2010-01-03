#include <stdio.h>

int main()
{
	static double a, b;

	while (scanf("%lf %lf", &a, &b) >= 2)
		printf("%.0f\n", (a >= b) ? (a - b) : (b - a));

	return 0;
}
