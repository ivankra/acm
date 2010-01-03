#include <stdio.h>

int main()
{
	static int a[64], i, n, c, s, r;

	for (c = 1; scanf("%d", &n) == 1 && n != 0; c++) {
		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);

		for (i = 0, s = 0; i < n; i++)
			s += a[i];

		s /= n;

		for (i = 0, r = 0; i < n; i++)
			if (a[i] > s) r += a[i] - s;

		printf("Set #%d\nThe minimum number of moves is %d.\n\n", c, r);
	}

	return 0;
}
