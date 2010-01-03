#include <stdio.h>

int main()
{
	static int c[32];
	int n, k, m, p, left, f, s;
	register int i, j;

	while (scanf("%d %d %d", &n, &k, &m) >= 3 && n && k && m) {
		for (i = 0; i < n; i++)
			c[i] = 1;

		for (p = 0, left = n, f = 0, s = n - 1; left > 0; p++) {
			for (j = (k - 1) % left; ; f++) {
				if (f >= n) f -= n;
				if (c[f] && j-- <= 0) break;
			}

			for (j = (m - 1) % left ; ; s--) {
				if (s < 0) s += n;
				if (c[s] && j-- <= 0) break;
			}

			c[f] = c[s] = 0;

			if (p != 0)
				putchar(',');

			if (f == s) {
				printf("%3d", f + 1);
				left--;
			} else {
				printf("%3d%3d", f + 1, s + 1);
				left -= 2;
			}
		}
		printf("\n");
	}

	return 0;
}
