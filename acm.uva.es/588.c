#include <stdio.h>

int x[1024], y[1024], n;

int solve()
{
	int i, minx, maxx, miny, maxy;

	for (minx = maxx = x[0], miny = maxy = y[0], i = 1; i < n; i++) {
		if (x[i] < minx) minx = x[i];
		if (y[i] < miny) miny = y[i];
		if (x[i] > maxx) maxx = x[i];
		if (y[i] > maxy) maxy = y[i];
	}

	for (i = 1;; i++) {
		if (minx > maxx) return 0;
		if (miny > maxy) return 0;
		if (i > n) return 1;

		/* +->
		   |xx */
		if (x[i - 1] == x[i] && y[i - 1] < y[i] && x[i] < x[i + 1]) {
			if (y[i] < maxy) maxy = y[i];
			if (x[i] > minx) minx = x[i];
		}

		/* >-+
		   xx| */
		if (y[i - 1] == y[i] && x[i - 1] < x[i] && y[i] > y[i + 1]) {
			if (y[i] < maxy) maxy = y[i];
			if (x[i] < maxx) maxx = x[i];
		}

		/* xx|
		   <-+ */
		if (x[i - 1] == x[i] && y[i - 1] > y[i] && x[i] > x[i + 1]) {
			if (y[i] > miny) miny = y[i];
			if (x[i] < maxx) maxx = x[i];
		}

		/* |xx
		   +-< */
		if (y[i - 1] == y[i] && x[i - 1] > x[i] && y[i] < y[i + 1]) {
			if (y[i] > miny) miny = y[i];
			if (x[i] > minx) minx = x[i];
		}
	}
}

int main()
{
	int i, t;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		for (i = 0; i < n; i++) {
			scanf("%d %d", &x[i], &y[i]);
			x[n + i] = x[i];
			y[n + i] = y[i];
		}

		printf("Floor #%d\nSurveillance is %spossible.\n\n",
			t, solve() ? "" : "im");
	}

	return 0;
}
