#include <stdio.h>
#include <string.h>

int main()
{
	static char s[1024][1024];
	int i, j, k, n, a;

	scanf("%d", &k);
	n = k * (k - 1) + 1;

	memset(s, '.', sizeof(s));

	for (i = 1; i <= n; i++) 
		for (j = 1; j <= k && scanf("%d", &a) == 1; j++)
			s[i][a] = '*';

	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) printf("%c ", s[i][j]);
		putchar('\n');
	}

	return 0;
}
