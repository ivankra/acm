#include <stdio.h>

int main()
{
	int i, j, k, n, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (i = 0, k = 2 * n + 1; i < n; i++, k += 2) {
			printf("%-5d", k);
			for (j = 0; j <= i; j++)
				printf(" %d", n * (n - i) + (n - 1) * j);
			printf("\n");
		}

		for (i = n - 1; i > 1; i--, k += 2) {
			printf("%-5d", k);
			for (j = 0; j < i; j++)
				printf(" %d", i + (n - 1) * j);
			printf("\n");
		}

		if (t != 0)
			printf("\n");
	}

	return 0;
}
