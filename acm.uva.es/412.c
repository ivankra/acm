#include <stdio.h>
#include <math.h>

static int gcd(int a, int b)
{
	static int k;

	for (k = 0; a && b && ((a | b) & 1) == 0; k++)
		a >>= 1, b >>= 1;

	for (;;) {
		if (a == 0) return (b << k);
		if (b == 0) return (a << k);

		while ((a & 1) == 0) a >>= 1;
		while ((b & 1) == 0) b >>= 1;

		if (a > b)
			a = (a - b) >> 1;
		else
			b = (b - a) >> 1;
	}
}


int main()
{
	static int a[64], s, i, j, t, n;
	static double r;

	while (scanf("%d", &n) == 1 && n != 0) {
		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);

		for (s = 0, i = 0, t = 0; i < n; i++)
			for (j = i + 1; j < n; j++, t++)
				if (gcd(a[i], a[j]) == 1) s++;

		if (s == 0) {
			printf("No estimate for this data set.\n");
		} else {
			r = sqrt((6. * (double)t) / (double)s);
			printf("%.6f\n", r);
		}
	}

	return 0;
}
