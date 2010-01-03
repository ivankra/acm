#include <stdio.h>
#include <string.h>

int a[512][512], w, h, n;
int x1, y1, x2, y2;

int solve()
{
	int i, j, k;

	if (n == 0)
		return w * h;

	for (i = 1; i <= h; i++)
		for (j = 1; j <= w; j++)
			a[i][j] = 1;

	while (n-- > 0 && scanf("%d %d %d %d", &x1, &y1, &x2, &y2) == 4) {
		if (x1 > x2)
			k = x1, x1 = x2, x2 = k;

		if (y1 > y2)
			k = y1, y1 = y2, y2 = k;

		for (i = y1; i <= y2; i++)
			for (j = x1; j <= x2; j++)
				a[i][j] = 0;
	}

	for (k = 0, i = 1; i <= h; i++)
		for (j = 1; j <= w; j++)
			k += a[i][j];

	return k;
}

int main()
{
	int r;

	while (scanf("%d %d %d", &w, &h, &n) == 3 && w > 0) {
		r = solve();

		if (r == 0)
			printf("There is no empty spots.\n");	
		else if (r == 1)
			printf("There is one empty spot.\n");
		else
			printf("There are %d empty spots.\n", r);
	}

	return 0;
}
