#include <stdio.h>
#include <math.h>

int main(void)
{
	double n, t;
	int i;

	for (i = 1; scanf("%lf", &n) > 0 && n >= 0.9; i++) {
		if (n > 1.5) {
			t = floor((3.0 + sqrt(9.0 + 8.0 * n)) / 2.0);
			while ((t * (t - 3)) < (2 * n))
				t += 1.0;
		} else {
			t = 4;
		}

		printf("Case %d: %.0f\n", i, t);
	}

	return 0;
}
