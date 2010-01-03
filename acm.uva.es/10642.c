#include <stdio.h>
#include <stdlib.h>

int get(int x, int y)
{
	int r = x + y;
	return r * (r + 1) / 2 + r - y;

}

int main()
{
	int c, t, x1, y1, x2, y2;

	for (scanf("%d", &t), c = 1; c <= t; c++) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		printf("Case %d: %d\n", c, abs(get(x2, y2) - get(x1, y1)));
	}

	return 0;
}
