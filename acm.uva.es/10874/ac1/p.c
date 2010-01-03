#include <stdio.h>

static int min(int a, int b)
{
	return (a < b) ? a : b;
}

static int abs(int a)
{
	return (a < 0) ? (-a) : a;
}

int main()
{
	int left, right, n;
	int i, t, x1, c1, x2, c2;

	while (scanf("%d", &n) == 1 && n > 0) {
		x1 = x2 = 1;
		c1 = c2 = 0;

		for (i = 1; i <= n; i++) {
			scanf("%d %d", &left, &right);

			t = min(c1 + abs(x1 - right), c2 + abs(x2 - right));
			c2 = min(c1 + abs(x1 - left), c2 + abs(x2 - left));
			c1 = t;

			c1 += right - left;
			c2 += right - left;

			if (i < n) { c1++; c2++; }

			x1 = left;
			x2 = right;
		}

		t = min(c1 + n - x1, c2 + n - x2);
		printf("%d\n", t);
	}

	return 0;
}
