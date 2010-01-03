#include <stdio.h>

int main()
{
	static int n, x, y, len, d[10], c[1024];
	register int i, k;

	while (scanf("%d", &n) == 1 && n != 0) {
		printf("Original number was %d\n", n);

		c[0] = n;
		len = 1;

		for (;;) {
			for (i = 0; i < 10; i++) d[i] = 0;
			for (i = 0, k = n; k > 0; k /= 10) d[k % 10]++;

			for (x = 0, i = 9; i >= 0; i--)
				for (k = 0; k < d[i]; k++) x = x * 10 + i;

			for (y = 0, i = 1; i <= 9; i++)
				for (k = 0; k < d[i]; k++) y = y * 10 + i;

			n = x - y;
			printf("%d - %d = %d\n", x, y, n);

			for (i = 0; i < len; i++)
				if (c[i] == n) break;

			if (i < len)
				break;

			c[len++] = n;
		}

		printf("Chain length %d\n\n", len);
	}

	return 0;
}
