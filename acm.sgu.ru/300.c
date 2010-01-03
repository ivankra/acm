#include <stdio.h>
#include <stdlib.h>

int x[4096], y[4096], z[4096], n, r;

int main()
{
	int i, j, k, x0, y0;

	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d %d", &x[i], &y[i]);

	for (z[0] = 0, i = 1; i < n; i++)
		z[i] = z[i-1] + abs(x[i] - x[i-1]) + abs(y[i] - y[i-1]);

	for (r = z[n-1], i = 1; i < n; i++) {
		for (j = i + 2; j < n; j++) {
			if (x[i] == x[j] && y[i] == y[j])
				x0 = x[i], y0 = y[i];
			else if (x[i] == x[j-1] && y[i] == y[j-1])
				x0 = x[i], y0 = y[i];
			else if (x[i-1] == x[j] && y[i-1] == y[j])
				x0 = x[j], y0 = y[j];
			else if (x[i-1] == x[j-1] && y[i-1] == y[j-1])
				x0 = x[i-1], y0 = y[i-1];
			else if (x[j-1] == x[j] && y[i-1] == y[i]) {
				x0 = x[j]; y0 = y[i];
				if (x0 < x[i-1] && x0 < x[i]) continue;
				if (x0 > x[i-1] && x0 > x[i]) continue;
				if (y0 < y[j-1] && y0 < y[j]) continue;
				if (y0 > y[j-1] && y0 > y[j]) continue;
			} else if (y[j-1] == y[j] && x[i-1] == x[i]) {
				x0 = x[i]; y0 = y[j];
				if (x0 < x[j-1] && x0 < x[j]) continue;
				if (x0 > x[j-1] && x0 > x[j]) continue;
				if (y0 < y[i-1] && y0 < y[i]) continue;
				if (y0 > y[i-1] && y0 > y[i]) continue;
			} else {
				continue;
			}

			k = z[j-1] - z[i];
			k += abs(x0 - x[i]) + abs(y0 - y[i]);
			k += abs(x0 - x[j-1]) + abs(y0 - y[j-1]);
			if (k < r) r = k;
		}
	}

	printf("%d\n", r);
	return 0;
}
