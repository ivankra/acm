#include <stdio.h>
#include <stdlib.h>

int main()
{
	static char buf[256];
	static int a[128], n;
	register int i, j, s;

	while (scanf("%d\n", &n) == 1 && n != 0) {
		for (i = 0; i < n; i++) {
			gets(buf);
			for (a[i] = 0, j = 0; buf[j]; j++)
				if (buf[j] == ' ') a[i]++;
		}

		for (s = a[0], i = 1; s > 0 && i < n; i++)
			if (a[i] < s) s = a[i];

		for (j = 0, i = 0; i < n; i++)
			j += a[i] - s;

		printf("%d\n", j);
	}

	return 0;
}
