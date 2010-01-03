#include <stdio.h>

int main()
{
	static int y[32], a[32], b[32], n, t;
	int i, c;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		for (i = 0; i < n; i++) {
			scanf("%d %d %d", &y[i], &a[i], &b[i]);
			b[i] -= a[i];
			y[i] -= a[i];
		}

		for (c = a[0], i = 1; i < n; i++)
			if (a[i] > c) c = a[i];

		for (; c < 10000; c++) {
			for (i = 0; i < n; i++)
				if (((c - a[i]) % b[i]) != y[i]) break;

			if (i >= n)
				break;
		}

		if (c < 10000)
			printf("Case #%d:\nThe actual year is %d.\n\n", t, c);
		else
			printf("Case #%d:\nUnknown bugs detected.\n\n", t);
	}

	return 0;
}
