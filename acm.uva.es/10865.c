#include <stdio.h>

int sign(int x)
{
	if (x < 0)
		return -1;
	else if (x == 0)
		return 0;
	else
		return 1;
}

int main()
{
	static int x[1048576], y[1048576], n, cx, cy, r1, r2;
	int i, j;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0; i < n; i++)
			scanf("%d %d", &x[i], &y[i]);

		cx = x[n >> 1];
		cy = y[n >> 1];

		for (i = r1 = r2 = 0; i < n; i++) {
			j = sign(x[i] - cx) * sign(y[i] - cy);

			if (j > 0)
				r1++;
			else if (j < 0)
				r2++;
		}

		printf("%d %d\n", r1, r2);
	}

	return 0;
}
