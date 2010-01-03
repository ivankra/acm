#include <stdio.h>

void solve(int k)
{
	int i, j, c, m, t;

	for (i = 0; i < k; i++) {
		printf("1");
		for (t = i * (k - 1) + 2, j = 1; j < k; j++, t++)
			printf(" %d", t);
		printf("\n");
	}

	for (m = k - 1, i = 0; i < m; i++) {
		for (c = 0; c < m; c++) {
			printf("%d", i + 2);
			for (j = 0; j < m; j++)
				printf(" %d", 2 + (k - 1) * (j + 1) + ((i * j + c) % m));
			printf("\n");
		}
	}
}

int main()
{
	int k, t = 0;

	while (scanf("%d", &k) == 1) {
		if (t++) printf("\n");
		solve(k);
	}

	return 0;
}
