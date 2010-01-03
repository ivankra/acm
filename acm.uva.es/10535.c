#include <stdio.h>

int ax[1024], ay[1024], bx[1024], by[1024], n;

int max(int x, int y) { return (x > y) ? x : y; }

int f(int x, int y)
{
	int i, k, t, s;

	if (x == 0 && y == 0)
		return 0;

	for (i = k = 0; i < n; i++) {
		t = ax[i] * y - ay[i] * x;
		s = bx[i] * y - by[i] * x;
		if ((t > 0 && s > 0) || (t < 0 && s < 0)) continue;

		t = ax[i] * (ay[i] - by[i]) - (ax[i] - bx[i]) * ay[i];
		s = x * (ay[i] - by[i]) - (ax[i] - bx[i]) * y;

		if (s != 0) {
			if ((t >= 0 && s >= 0) || (t <= 0 && s <= 0)) k++;
		} else {
			s = ax[i] * x + ay[i] * y;
			t = bx[i] * x + by[i] * y;
			if (s >= 0 || t >= 0) k++;
		}
	}

	return k;
}

int main()
{
	int i, j, x0, y0;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0; i < n; i++)
			scanf("%d %d %d %d", &ax[i], &ay[i], &bx[i], &by[i]);

		scanf("%d %d", &x0, &y0);
		for (i = 0; i < n; i++) {
			ax[i] -= x0; ay[i] -= y0;
			bx[i] -= x0; by[i] -= y0;
		}

		for (i = j = 0; i < n; i++)
			j = max(j, max(f(ax[i], ay[i]), f(bx[i], by[i])));
		printf("%d\n", j);
	}

	return 0;
}
