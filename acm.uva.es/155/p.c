/* Problem 155. "All Squares." */
#include <stdio.h>

int n, k, px, py;

static void square(int x, int y, int h)
{
	if (px >= (x - h) && px <= (x + h) &&
	    py >= (y - h) && py <= (y + h))
		n++;

	if (h > 1) {
		square(x - h, y - h, h >> 1);
		square(x + h, y - h, h >> 1);
		square(x - h, y + h, h >> 1);
		square(x + h, y + h, h >> 1);
	}
}

int main()
{
	while (scanf("%d %d %d", &k, &px, &py) == 3) {
		if (k == 0 && px == 0 && py == 0)
			break;

		n = 0;
		square(1024, 1024, k);

		printf("%3d\n", n);
	}
	return 0;
}
