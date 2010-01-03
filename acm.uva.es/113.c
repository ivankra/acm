#include <stdio.h>
#include <math.h>

int main()
{
	long double a, x, y, z, u, v;
	int i, n;

	while (scanf("%d %Lf", &n, &a) >= 2) {
		for (x = a, u = n, v = n - 1; x > 0.; x = y) {
			for (i = n - 1, z = 1., y = x; i > 0; i >>= 1, y *= y)
				if (i & 1) z *= y;

			y = (x * v + (a / z)) / u;
			if (y >= x)
				  break;
		}

		if ((ceil(x) - x) < (x - floor(x)))
			printf("%d\n", (int)ceil(x));
		else
			printf("%d\n", (int)floor(x));
	}

	return 0;
}
