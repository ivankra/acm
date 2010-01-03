#include <stdio.h>

int main()
{
	static int x[1024], y[1024], px, py, n;
	int i, m;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0; i < n; i++)
			scanf("%d%d", &x[i], &y[i]);
		x[n] = x[0]; y[n] = y[0];
		scanf("%d%d", &px, &py);

		for (i = 0, m = 0; i < n; i++) {
			if (x[i] != x[i + 1])
				continue;

			if (x[i] >= px)
				continue;

			if (y[i] < y[i + 1]) {
				if (y[i + 1] <= py || y[i] >= py) continue;
			} else {
				if (y[i] <= py || y[i + 1] >= py) continue;
			}

			m++;
		}

		printf((m & 1) ? "T\n" : "F\n");
	}

	return 0;
}
