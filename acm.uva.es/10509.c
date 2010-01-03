#include <stdio.h>
#include <math.h>

int main()
{
	double a, n;
	int i, m;

	while (scanf("%lf", &n) == 1 && n != 0.) {
		m = floor(n + 1e-9);
		for (i = 1; (i * i * i) <= m; i++);

		a = i - 1;
		printf("%.4f\n", a + (n - a * a * a) / (3. * a * a));
	}

	return 0;
}
