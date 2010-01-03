#include <stdio.h>

int main()
{
	int i, j, c, t, n;

	for (scanf("%d", &t), c = 1; c <= t && scanf("%d", &n) == 1; c++) {
		for (i = 2; (n % i) != 0; i++);
		for (j = i + 1; (n % j) != 0; j++);
		printf("Case #%d: %d = %d * %d = %d * %d\n", c, n, i, n/i, j, n/j);
	}

	return 0;
}
