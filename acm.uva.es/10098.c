#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static void permute(char *p, int n)
{
	int i, j, k;
	char c;

	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
			if (p[j] < p[i]) { c = p[i]; p[i] = p[j]; p[j] = c; }

	for (;;) {
		p[n] = '\n';
		fwrite(p, 1, n+1, stdout);

		for (i = n - 1; i >= 0; i--)
			if (p[i] < p[i+1]) break;
		if (i < 0) break;

		for (k = i + 1, j = i + 2; j < n; j++)
			if (p[j] > p[i] && p[j] < p[k]) k = j;

		c = p[i]; p[i] = p[k]; p[k] = c;
		for (i++; i < n; i++)
			for (j = n - 1; j > i; j--)
				if (p[j] < p[i]) { c=p[i]; p[i]=p[j]; p[j]=c; }
	}
}

int main(void)
{
	static char buf[256];	
	int case_no, i, c;

	scanf("%d\n", &case_no);
	while (case_no-- > 0) {
		while ((c = getchar()) != EOF && !isalpha(c));
		for (i = 0; c != EOF && isalpha(c) && (i < (sizeof(buf)-2));) {
			buf[i++] = c;
			c = getchar();
		}
		buf[i] = '\0';

		permute(buf, i);
		printf("\n");
	}

	return 0;
}
