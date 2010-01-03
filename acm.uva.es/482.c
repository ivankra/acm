#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXN 65536

static int p[MAXN], t;
static char *a[MAXN], *b[MAXN], buf[65536];

int main()
{
	static int valid[256];
	int n, c, i, j;

	for (i = 0; i < 256; i++) valid[i] = 0;
	for (i = 0; (c = "0123456789+-.Ee"[i]) != '\0'; i++) valid[c] = 1;

	scanf("%d", &t);

	while (t-- > 0) {
		for (n = 0;;) {
			while ((c = getchar()) != EOF && c != '\n' && !isdigit(c));
			if (c == EOF || (c == '\n' && n != 0)) break;
			if (c == '\n') continue;
			for (p[n] = 0; c >= '0' && c <= '9'; c = getchar())
				p[n] = p[n] * 10 + c - '0';
			if (c != EOF) ungetc(c, stdin);
			n++;
		}

		if (n == 0)
			break;

		for (i = 0; i < n; i++)
			a[i] = NULL, b[i] = NULL;

		for (i = 0; i < n;) {
			while ((c = getchar()) != EOF && !valid[c]);
			if (c == EOF) break;
			for (j = 0; c != EOF && valid[c]; c = getchar())
				buf[j++] = c;
			if (c != EOF) ungetc(c, stdin);
			buf[j] = '\0';
			a[i] = (char *)malloc(j + 1);
			strcpy(a[i], buf);
			i++;
		}

		for (i = 0; i < n; i++)
			b[p[i] - 1] = a[i];

		for (i = 0; i < n; i++)
			printf("%s\n", b[i] ? b[i] : "");

		for (i = 0; i < n; i++)
			if (a[i]) free(a[i]);

		if (t > 0)
			printf("\n");
	}

	return 0;
}
