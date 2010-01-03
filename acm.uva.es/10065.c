#include <stdio.h>
#include <stdlib.h>

#define SQ(x) ((x) * (x))

int hull(int x[], int y[], int n)
{
	static int p[1024];
	int i, j, k, h, t;

	for (k = 0, i = 1; i < n; i++)
		if (x[i] < x[k] || (x[i] == x[k] && y[i] < y[k])) k = i;

	for (h = 1, p[0] = k;;) {
		for (i = 0, j = -1; i < n; i++) {
			if (x[i] == x[k] && y[i] == y[k])
				continue;

			if (j < 0) {
				j = i;
				continue;
			}

			t = (x[i] - x[k]) * (y[j] - y[k]) - (x[j] - x[k]) * (y[i] - y[k]);

			if (t < 0)
				continue;

			if (t == 0) {
				t = SQ(x[i] - x[k]) + SQ(y[i] - y[k])
				    - SQ(x[j] - x[k]) - SQ(y[j] - y[k]);

				if (t < 0)
					continue;
			}

			j = i;
		}

		if (j < 0 || j == p[0])
			break;

		p[h++] = j;
		k = j;
	}

	p[h] = p[0];

	for (k = 0, i = 0; i < h; i++)
		k += x[p[i]] * y[p[i + 1]] - x[p[i + 1]] * y[p[i]];

	return k;
}

int area(int x[], int y[], int n)
{
	int a, i;

	for (a = 0, i = 0; i < n; i++)
		a += x[i] * y[i + 1] - x[i + 1] * y[i];

	return abs(a);
}

int main()
{
	static int x[128], y[128], n, t;
	int i;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		for (i = 0; i < n; i++)
			scanf("%d %d", &x[i], &y[i]);

		x[n] = x[0];
		y[n] = y[0];

		printf("Tile #%d\nWasted Space = %.2f %%\n\n", t,
			100. * (1. - ((double)area(x, y, n) / (double)hull(x, y, n))) + 1e-12);
	}

	return 0;
}
