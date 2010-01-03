#include <stdio.h>
#include <stdlib.h>

int cmp(const void *p, const void *q)
{
	return *(int *)q - *(int *)p;
}

int main()
{
	static int a[65536], c, n;
	int i, j, k;

	for (c = 1; scanf("%d", &n) == 1 && n > 0; c++) {
		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);

		qsort(a, n, sizeof(a[0]), &cmp);

		for (i = j = k = 0; i < n; i++) {
			k += j;
			if (a[i] > a[i + 1]) j++;
		}

		printf("Case %d: %d\n", c, k);
	}

	return 0;
}
