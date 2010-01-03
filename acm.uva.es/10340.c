#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLEN 150000

int main()
{
	static int buf1[MAXLEN], buf2[MAXLEN];
	static char a[MAXLEN], b[MAXLEN];
	int *cur, *next;
	int i, j, m, n, c;

	for (;;) {
		for (m = 0; (c = getchar()) != EOF;)
			if (isalnum(c))
				a[m++] = c;
			else if (m != 0)
				break;
		if (m == 0) break;

		for (n = 0; (c = getchar()) != EOF;)
			if (isalnum(c))
				b[n++] = c;
			else if (n != 0)
				break;

		if (n == 0) break;

		if (m > n) {
			printf("No\n");
			continue;
		}

		for (i = 0; i < n; i++)
			buf1[i] = 0;

		for (i = 0, cur = buf1, next = buf2; i < m; i++) {
			next[0] = (a[i] == b[0]) ? 1 : 0;;
			for (j = 1; j < n; j++) {
				if (a[i] == b[j])
					next[j] = cur[j - 1] + 1;
				else if (next[j - 1] <= cur[j])
					next[j] = cur[j];
				else
					next[j] = next[j - 1];
			}

			if (cur == buf1) {
				cur = buf2;
				next = buf1;
			} else {
				cur = buf1;
				next = buf2;
			}

			if (cur[n - 1] >= m)
				break;
		}

		printf((cur[n - 1] >= m) ? "Yes\n" : "No\n");
	}

	return 0;
}
