#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int count, result[65536][24], resn[65536];
int fact[32];

int search(int num, int k, int x0)
{
	int x;

	if (num == 1 && k >= 2) {
		resn[count] = k;
		for (x = 0; x < k; x++)
			result[count][x] = fact[x];
		count++;
		return;
	}

	for (x = x0; (x * x) <= num; x++) {
		if ((num % x) != 0) continue;

		fact[k] = x;
		search(num / x, k + 1, x);

		if ((x * x) != num) {
			fact[k] = num / x;
			search(x, k + 1, num / x);
		}
	}

	if (num >= x0) {
		fact[k] = num;
		search(1, k + 1, num);
	}
}

int main()
{
	int i, j, n;

	while (scanf("%d", &n) == 1 && n > 0) {
		count = 0;
		search(n, 0, 2);

		printf("%d\n", count);

		for (i = 0; i < count; i++) {
			for (j = 0; j < resn[i]; j++)
				printf(j ? " %d" : "%d", result[i][j]);
			printf("\n");
		}
	}

	return 0;
}
