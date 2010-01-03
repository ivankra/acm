#include <stdio.h>

int main()
{
	static int a[1024], m, n, t, res, r;
	register int i, j, k;

	scanf("%d", &t);

	while (t-- > 0 && scanf("%d %d", &m, &n) == 2) {
		for (i = 0; i < n; i++)
			a[i] = 0;

		for (r = 0, res = 0; r < m; r++) {
			for (i = 0; i < n;) {
				k = getchar();
				if (k == 'R')
					a[i++] = 0;
				else if (k == 'F')
					a[i++]++;
			}

			for (i = 0; i < n; i++) {
				if (a[i] > res)
					res = a[i];

				for (j = i + 1, k = a[i]; j < n; j++) {
					if (a[j] < k)
						k = a[j];

					if ((k * (j - i + 1)) > res)
						res = k * (j - i + 1);
				}
			}

		}

		printf("%d\n", res * 3);
	}

	return 0;
}
