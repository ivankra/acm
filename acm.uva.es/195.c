#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define LESS_THAN(a,b) \
	((toupper(a) < toupper(b)) || (toupper(a) == toupper(b) && (a) < (b)))

static void permute(char *p, int n)
{
	register int i, j, k;
	register char c;

	if (n < 2) {
		for (i = 0; i < n; i++) putchar(p[i]);
		putchar('\n');
		return;
	}

	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
			if (LESS_THAN(p[j], p[i]))
				{ c=p[i]; p[i]=p[j]; p[j]=c; }

	for (;;) {
		p[n] = '\n';
		fwrite(p, 1, n + 1, stdout);

		for (i = n - 1; i >= 0; i--)
			if (LESS_THAN(p[i], p[i + 1])) break;
		if (i < 0) break;

		for (k=(i+1), j=(i+2); j < n; j++)
			if (LESS_THAN(p[i], p[j]) && LESS_THAN(p[j], p[k]))
				k = j;

		c = p[i]; p[i] = p[k]; p[k] = c;
		for (i++; i < n; i++)
			for (j = i + 1; j < n; j++)
				if (LESS_THAN(p[j], p[i]))
					{ c=p[i]; p[i]=p[j]; p[j]=c; }
	}
}

int main(void)
{
	static char buf[8096];
	int case_no, i, c;

	scanf("%d\n", &case_no);
	while (case_no-- > 0) {
		while ((c = getchar()) != EOF && !isalpha(c));
		for (i = 0;;) {
			if (i < (sizeof(buf) - 1))
				buf[i++] = c;
			if ((c = getchar()) == EOF || !isalpha(c)) break;
		}
		buf[i] = '\0';

		permute(buf, i);
	}

	return 0;
}
