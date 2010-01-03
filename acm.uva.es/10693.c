#include <stdio.h>
#include <math.h>

int main()
{
	int l, f;
	double v;

	while (scanf("%d %d", &l, &f) == 2 && l > 0) {
		v = sqrt(2. * l * f);
		printf("%.8f %.8f\n", v, 1800. * v / (double)l);
	}

	return 0;
}
