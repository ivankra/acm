#include <stdio.h>

int main()
{
	static int a[16], b[1048576], m, n;
	int i, j, t;

	while (scanf("%d %d", &n, &m) == 2) {
		for (i = 0; i < m;) {
			scanf("%d", &a[i]);
			if (a[i] >= 1) i++; else m--;
		}

		for (i = 0; i < m; i++) {
			for (t = a[i], j = i - 1; j >= 0 && a[j] > t; j--)
				a[j + 1] = a[j];
			a[j + 1] = t;
		}

		a[m] = 0x7FFFFFF;
		for (b[0] = 0, i = 1; i <= n; i++) {
			b[i] = 0;
			for (j = 0; a[j] <= i; j++)
				if (b[i - a[j]] == 0) {
					b[i] = 1;
					break;
				}
		}

		printf(b[n] ? "Stan wins\n" : "Ollie wins\n");
	}

	return 0;
}
