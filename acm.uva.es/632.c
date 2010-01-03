#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char s[4096], *p[4096], buf[4096];
static int n, t;

static int cmp(const void *p, const void *q)
{
	register int r;

	if ((r = memcmp(*(char **)p, *(char **)q, n)) != 0)
		return r;
	else
		return ((*(char **)p > *(char **)q) ? 1 : -1);
}

int main()
{
	register int i, j, k;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (i = 0; i < n && gets(buf);) {
			for (j = 0; i < n && buf[j];)
				s[i++] = buf[j++];
		}

		for (j = 0; j < n;)
			s[i++] = s[j++];

		for (i = 0; i < n; i++)
			p[i] = &s[i];

		qsort(p, n, sizeof(char *), &cmp);

		for (i = 0; i < n; i++)
			if (p[i] == &s[1]) break;
		printf("%d\n", i);

		for (i = 0, j = 0, k = 0; i < n; i++) {
			if (k++ >= 50) {
				buf[j++] = '\n';
				k = 1;
			}
			buf[j++] = p[i][n - 1];
		}

		buf[j++] = '\n';

		if (t > 0)
			buf[j++] = '\n';

		buf[j] = '\0';

		fwrite(buf, 1, j, stdout);
	}

	return 0;
}
