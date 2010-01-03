#include <stdio.h>

int main()
{
	int i, j, k, m, n, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (i = 1, m = n - 1, k = 2 * n + 1; i <= n; i++, k += 2) {
			printf("%-5d", k);
			for (j = 0; j < i; j++)
				printf(" %d", i + m * j);
			printf("\n");
		}

		for (i = 2; i < n; i++, k += 2) {
			printf("%-5d", k);
			for (j = n - i; j >= 0; j--)
				printf(" %d", i * n + j * m);
			printf("\n");
		}

		if (t != 0)
			printf("\n");
	}

	return 0;
}
