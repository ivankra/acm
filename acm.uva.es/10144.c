#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	static char buf[65536], *table[128];
	int i, n, t;

	table[0] = "((A0|B0)|(A0|B0))";

	for (i = 1; i <= 100; i++) {
		sprintf(buf,
			"((A%d|B%d)|(%s|((A%d|A%d)|(B%d|B%d))))",
			i, i, table[i - 1], i, i, i, i
		);

		table[i] = malloc(strlen(buf) + 1);
		strcpy(table[i], buf);
	}

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;)
		printf(t ? "%s\n\n" : "%s\n", table[n - 1]);

	return 0;
}
