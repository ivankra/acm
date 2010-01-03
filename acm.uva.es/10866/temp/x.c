#include <stdio.h>
#include <string.h>

int main()
{
	char s[1024];
	int i, j, k, n;

	while (scanf(" %s", s) == 1) {
		n = strlen(s);
		s[n] = 'x'; s[n+1] = '\0';

		for (k = 1; k <= n; k++) {
			printf("%3d  ", k);
			for (i = 0, j = k - 1; i < n; i++, j = (j + k) % (n + 1))
				putchar(s[j]);
			printf("\n");
		}

		printf("\n");
	}

	return 0;
}
