#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char sep[] = "------------------------------------------------------------\n";

int main()
{
	static char list[128][64];
	static int n, l, c, r;
	register int i, j;

	while (scanf("%d\n", &n) == 1) {
		memset(list, '\0', sizeof(list));
		for (i = 0; i < n; i++)
			scanf(" %63[^\n]\n", list[i]);

		qsort(list, n, sizeof(list[0]),
		      (int (*)(const void *, const void *))&strcmp);

		for (i = 0, l = 0; i < n; i++)
			if (i == 0 || strlen(list[i]) > l)
				l = strlen(list[i]);

		c = 62 / (l + 2);
		r = (n + c - 1) / c;

		printf(sep);

		for (i = 0; i < r; i++)
			for (j = 0; j < c; j++)
				printf(
					((j + 1) >= c) ? "%-*s\n" : "%-*s  ",
					l, ((j*r+i) >= n) ? "" : list[j*r+i]
				);
	}

	return 0;
}
