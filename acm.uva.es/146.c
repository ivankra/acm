#include <stdio.h>

int main(void)
{
	static char p[256];
	int i, j, k, c, n;

	for (;;) {
		while ((c = getchar()) != EOF && !(c>='a' && c<='z') && c!='#');
		if (c == '#' || c == EOF) break;
		for (n = 0; c != EOF && c>='a' && c<='z' && n<(sizeof(p)-1);) {
			p[n++] = c;
			c = getchar();
		}
		p[n] = '\n';

		for (i = n - 2; i >= 0; i--)
			if (p[i] < p[i + 1]) break;

		if (i < 0) {
			printf("No Successor\n");
			continue;
		}

		for (k = i + 1, j = i + 2; j < n; j++)
			if (p[j] > p[i] && p[j] < p[k]) k = j;

		c = p[i];
		p[i] = p[k];
		p[k] = c;

		while (++i < n)
			for (j = n - 1; j > i; j--)
				if (p[j] < p[i]) { c=p[i]; p[i]=p[j]; p[j]=c; }

		fwrite(p, 1, n + 1, stdout);
	}

	return 0;
}
