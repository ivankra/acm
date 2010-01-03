#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORDS 8096

static char words[MAXWORDS][256];
static int n;

static int cmp(const void *p, const void *q)
{
	return strcmp(words[*(int *)p], words[*(int *)q]);
}

static void reduce(int prn)
{
	static int idx[MAXWORDS], flag[MAXWORDS];
	int i, j;

	for (i = 0; i < n; i++)
		idx[i] = i, flag[i] = 1;

	qsort(idx, n, sizeof(char *), &cmp);

	if (prn) {
		for (i = 0; i < n; i++)
			if (i == 0 ||
			    strcmp(words[idx[i - 1]], words[idx[i]]) != 0)
				printf("%s\n", words[idx[i]]);
		return;
	}

	for (i = 1; i < n; i++)
		if (strcmp(words[idx[i - 1]], words[idx[i]]) == 0)
			flag[idx[i]] = 0;

	for (i = 0, j = 0; i < n; i++) {
		if (flag[i] == 0)
			continue;

		if (j < i)
			strcpy(words[j], words[i]);

		j++;
	}

	n = j;
}

int main()
{
	static int lwr[256];
	int i, c;

	for (i = 0; i < 256; i++)
		lwr[i] = ((i >= 'a' && i <= 'z') ? i :
			  ((i >= 'A' && i <= 'Z') ? (i - 'A' + 'a') : 0));

	for (n = 0, i = 0; (c = getchar()) != EOF && n < MAXWORDS;) {
		if (lwr[c]) {
			words[n][i++] = lwr[c];
		} else if (i != 0) {
			words[n++][i] = '\0';
			i = 0;

			if (n >= (MAXWORDS - 16))
				reduce(0);
		}
	}

	reduce(1);

	return 0;
}
