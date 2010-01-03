#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	static char s[1024];
	int a0, i, n, k, x0, x1, y0, y1;
	long long a, a2, x, y;

	while (scanf(" %[0-9^] %d", s, &a0) == 2) {
		if (strcmp(s, "0") == 0)
			break;

		if (strchr(s, '^') != NULL) {
			for (i = atoi(strchr(s, '^') + 1), n = 1; i-- > 0;)
				n *= 10;
		} else {
			n = atoi(s);
		}

		a = (long long)a0 * 10000000LL;
		a2 = (long long)a * (long long)a;

		for (k = 0, i = 0; i < n; i++) {
			scanf("%d.%d %d.%d", &x0, &x1, &y0, &y1);
			x = x0 * 10000000LL + x1;
			y = y0 * 10000000LL + y1;

			if ((x * x + y * y) > a2)
				continue;

			if (((x - a) * (x - a) + y * y) > a2)
				continue;

			if ((x * x + (y - a) * (y - a)) > a2)
				continue;

			if (((x - a) * (x - a) + (y - a) * (y - a)) > a2)
				continue;

			k++;
		}

		x = (long long)k * (long long)a0 * (long long)a0 * 100000LL / (long long)n;
		printf("%d.%.5d\n", (int)(x / 100000LL), (int)(x % 100000LL));
	}

	return 0;
}
