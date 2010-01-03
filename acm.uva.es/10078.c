#include <stdio.h>

int main()
{
	static int x[1024], y[1024], n, c1, c2;
	int i, j;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0; i < n; i++)
			scanf("%d %d", &x[i], &y[i]);

		x[n] = x[0];
		y[n] = y[0];
		x[n + 1] = x[1];
		y[n + 1] = y[1];

		for (c1 = c2 = i = 0; i < n; i++) {
			j = (x[i + 1] - x[i]) * (y[i + 2] - y[i]) - (x[i + 2] - x[i]) * (y[i + 1] - y[i]);

			if (j > 0)
				c1++;
			else if (j < 0)
				c2++;
		}

		printf((c1 == 0 || c2 == 0) ? "No\n" : "Yes\n");
	}

	return 0;
}
