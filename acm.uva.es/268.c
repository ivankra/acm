#include <stdio.h>

int main()
{
	static int a[65536];
	int i, j, b, m, n, z;

	while (scanf("%d", &b) == 1) {
		printf("For base %d the double-trouble number is\n", b);

		m = 2 * b - 1;
		for (i = b, n = 1;; n++, i = (i * b) % m) {
			for (z = 1; z < b; z++)
				if (((z * (i + m - 2)) % m) == 0) break;
			if (z < b) break;
		}

		m = n + 2;
		for (i = 0; i < m; i++)
			a[i] = 0;
		a[n] = 1;

		for (j = 2, i = 0; i < m; i++) {
			a[i] -= j;
			if (a[i] < 0) {
				a[i] += b;
				j = 1;
			} else {
				break;
			}
		}

		for (i = j = 0; i < m; i++, j /= b)
			a[i] = (j += a[i] * z) % b;

		for (i = m - 1, j = 0; i--; j %= (2 * b - 1))
			a[i] = (j = j * b + a[i]) / (2 * b - 1);

		for (i = n; i--;)
			printf("%d ", a[i]);
		printf("%d \n", z);
	}

	return 0;
}
