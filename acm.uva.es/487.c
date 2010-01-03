#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int a[32][32], n, maxlen, nwords;
static char word[1024], wbuf[1048576], *words[131072];

static void search(int r, int c, int k)
{
	word[k] = a[r][c];

	if ((k + 1) >= maxlen) {
		word[k + 1] = '\0';
		strcpy(words[nwords], word);
		words[nwords + 1] = words[nwords] + k + 2;
		nwords++;
		return;
	}

	if (a[r - 1][c - 1] > a[r][c]) search(r - 1, c - 1, k + 1);
	if (a[r - 1][c] > a[r][c]) search(r - 1, c, k + 1);
	if (a[r - 1][c + 1] > a[r][c]) search(r - 1, c + 1, k + 1);

	if (a[r][c - 1] > a[r][c]) search(r, c - 1, k + 1);
	if (a[r][c + 1] > a[r][c]) search(r, c + 1, k + 1);

	if (a[r + 1][c - 1] > a[r][c]) search(r + 1, c - 1, k + 1);
	if (a[r + 1][c] > a[r][c]) search(r + 1, c, k + 1);
	if (a[r + 1][c + 1] > a[r][c]) search(r + 1, c + 1, k + 1);
}

int compare(const void *p, const void *q)
{
	return strcmp(*(char **)p, *(char **)q);
}

int main()
{
	int t, i, j, c;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		memset(a, '\0', sizeof(a));

		for (i = 1; i <= n; i++)
			for (j = 1; j <= n && (c = getchar()) != EOF;)
				if (c != '\n') a[i][j++] = c;

		for (maxlen = 3;; maxlen++) {
			nwords = 0;
			words[0] = wbuf;

			for (i = 1; i <= n; i++)
				for (j = 1; j <= n; j++)
					search(i, j, 0);

			if (nwords == 0)
				break;

			qsort(words, nwords, sizeof(char *), &compare);

			for (i = 0; i < nwords; i++)
				if (i == 0 || strcmp(words[i], words[i-1]) != 0)
					printf("%s\n", words[i]);
		}

		if (t > 0)
			printf("\n");
	}

	return 0;
}
