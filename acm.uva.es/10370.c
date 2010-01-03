#include <stdio.h>

int main()
{
	static int n, a[1024], t;
	register int i, k, s;

	scanf("%d", &t);
	while (t-- > 0 && scanf("%d", &n) == 1) {
		for (i = 0, s = 0; i < n; s += a[i++])
			scanf("%d", &a[i]);

		for (k = 0, i = 0; i < n; i++)
			if ((a[i] * n) > s) k++;

		printf("%.3f%%\n", (double)k * 100. / (double)n);
	}

	return 0;
}
