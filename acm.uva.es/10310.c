#include <stdio.h>

#define SQ(x) ((x) * (x))

int main()
{
	static double gx, gy, dx, dy, hx, hy, rx=0, ry=0, d, g;
	static int n, r;

	while (scanf("%d %lf %lf %lf %lf", &n, &gx, &gy, &dx, &dy) == 5) {
		r = 0;

		while (n-- > 0 && scanf("%lf %lf", &hx, &hy) == 2) {
			if (r)
				continue;

			d = SQ(hx - dx) + SQ(hy - dy);
			g = (SQ(hx - gx) + SQ(hy - gy)) * 4. - 0.000000001;

			if (g < d) {
				r = 1;
				rx = hx;
				ry = hy;
			}
		}

		if (r)
			printf("The gopher can escape through the hole "
			       "at (%.3f,%.3f).\n", rx, ry);
		else
			printf("The gopher cannot escape.\n");
	}

	return 0;
}
