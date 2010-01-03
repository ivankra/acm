#include <stdio.h>

int main()
{
	static double r[8192], p, lo, x;
	int i, n, m, k;

	while (scanf("%d %lf %lf %d", &n, &p, &lo, &m) == 4 && n >= 0) {
		for (i = 0; m-- > 0 && scanf("%d %lf", &k, &x) == 2;) {
			for (; i < k; i++)
				r[i] = r[i - 1];

			r[i++] = x;
		}

		for (; i <= n; i++)
			r[i] = r[i - 1];

		x = (lo + p) * (1 - r[0]);
		p = lo / (double)n;

		for (i = 0; i < n; i++) {
			if (lo < (x - 1e-10))
				break;

			x *= (1 - r[i+1]);

			lo -= p;
			if (lo < 0) lo = 0.;
		}

		printf("%d month%s\n", i, (i != 1) ? "s" : "");
	}

	return 0;
}
