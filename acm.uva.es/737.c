#include <stdio.h>

int main()
{
	static int x, y, z, d, n, v;
	int x1, y1, z1, x2, y2, z2;

	while (scanf("%d", &n) == 1 && n > 0) {
		scanf("%d %d %d %d", &x1, &y1, &z1, &d);
		x2 = x1 + d;
		y2 = y1 + d;
		z2 = z1 + d;

		while (n-- > 1 && scanf("%d %d %d %d", &x, &y, &z, &d) == 4) {
			if (x > x1) x1 = x;
			if (y > y1) y1 = y;
			if (z > z1) z1 = z;

			x += d;
			y += d;
			z += d;

			if (x < x2) x2 = x;
			if (y < y2) y2 = y;
			if (z < z2) z2 = z;
		}

		if (x1 < x2 && y1 < y2 && z1 < z2)
			v = (x2 - x1) * (y2 - y1) * (z2 - z1);
		else
			v = 0;

		printf("%d\n", v);
	}

	return 0;
}
