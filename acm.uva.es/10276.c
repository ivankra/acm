#include <stdio.h>

/* greedy */

static int issquare(int a)
{
	register int x, y;

	if (a <= 1) return 1;

	for (x = a; ; x = y) {
		y = (x + (a / x)) >> 1;
		if (y >= x) break;
	}

	return (x * x) == a;
}

int main()
{
	static int a[128];
	int i, j, n, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		memset(a, 0, sizeof(a));

		for (i = 1; ; i++) {
			for (j = 0; j < n; j++)
				if (a[j] == 0 || issquare(a[j] + i)) break;

			if (j < n)
				a[j] = i;
			else
				break;
		}

		printf("%d\n", i - 1);
	}

	return 0;
}
