#include <stdio.h>

int main()
{
	double w, c, s;

	while (scanf("%lf %lf %lf", &w, &c, &s) == 3)
		printf("%.5f\n", c * (w + c - 1) / ((w + c) * (w + c - s - 1)));

	return 0;
}
