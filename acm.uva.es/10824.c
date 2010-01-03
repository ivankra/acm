#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

#define ISZERO(x) ((-10e-8 < (x)) && ((x) < 10e-8))

static int n;
static double pt[2048], pi;

int compare(const void *p, const void *q)
{
	return ((*(double *)p) < (*(double *)q)) ? -1 : 1;
}

static int query(int s, double x)
{
	register int a, b, c;

	for (a = s, b = n - 1; a <= b;) {
		c = (a + b) >> 1;

		if (ISZERO(pt[c] - x))
			return c;
		else if (pt[c] < x)
			a = c + 1;
		else
			b = c - 1;
	}

	return -1;
}

int main()
{
	static double x, y, d;
	static int t, count;
	int i, j, k, m, s;

	pi = 2. * acos(0.);

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		printf("Case %d:\n", t);

		for (i = 0; i < n && scanf("%lf %lf", &x, &y) == 2; i++)
			pt[i] = atan2(y, x) / (2. * pi);

		qsort(pt, n, sizeof(pt[0]), &compare);

		for (k = 3; k <= n; k++) {
			d = 1 / (double)k;

			for (s = 0, count = 0; (s + k) <= n; s++) {
				x = pt[s] + d;

				for (i = 1, j = s + 1; i < k; i++) {
					m = query(j, x);
					if (m < 0)
						break;

					x += d;
					j = m + 1;
				}

				if (i == k)
					count++;
			}

			if (count != 0)
				printf("%d %d\n", k, count);
		}
	}

	return 0;
}
