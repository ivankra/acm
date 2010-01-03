#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	static char s[1024], t[2048][80];
	int i, k, n;

	gets(s) && sscanf(s, "%d", &n);

	for (i = 0; i < n; i++)
		gets(s) && sscanf(s, " %s", t[i]);

	qsort(t, n, sizeof(t[0]), strcmp);

	if (n == 0)
		return 0;

	for (i = k = 1; i < n; i++) {
		if (strcmp(t[i - 1], t[i]) != 0) {
			printf("%s %d\n", t[i - 1], k);
			k = 1;
		} else {
			k++;
		}
	}

	printf("%s %d\n", t[n - 1], k);
	return 0;
}
