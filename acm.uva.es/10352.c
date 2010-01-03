#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define HDIV	65521
#define HSIZE	65536

int htab[HDIV], hnext[HSIZE], hcount[HSIZE], hfree;
char wbuf[1048576], *wnext, *hdata1[HSIZE], *hdata2[HSIZE];

int cmp(const void *p, const void *q)
{
	return strcmp(hdata1[*(int *)p], hdata1[*(int *)q]);
}

void add()
{
	unsigned i, j, h;

	for (h = 0, i = 0; wnext[i]; i++) {
		if (i == 2) continue;
		h = h * 61 + wnext[i];
		if (h > HDIV) h %= HDIV;
	}

	for (i = htab[h]; i != 0; i = hnext[i]) {
		if (strlen(wnext) != strlen(hdata1[i])) continue;

		for (j = 0; wnext[j]; j++) {
			if (j == 2 && hdata1[i][j] != '\0') continue;
			if (wnext[j] != hdata1[i][j]) break;
		}

		if (wnext[j] == '\0' && hdata1[i][j] == '\0') {
			hcount[i]++;
			strcpy(hdata2[i], wnext);
			return;
		}
	}

	i = hfree++;
	hcount[i] = 1;
	hnext[i] = htab[h];
	htab[h] = i;
	hdata1[i] = wnext;
	while (*wnext++ != '\0');
	strcpy(hdata2[i] = wnext, hdata1[i]);
	while (*wnext++ != '\0');

	if (strlen(hdata1[i]) >= 3)
		hdata1[i][2] = ' ';
}

int main()
{
	int i, j, t;

	for (t = 1;; t++) {
		wnext = wbuf;
		hfree = 1;
		memset(htab, 0, sizeof(htab));

		for (i = 0; (j = getchar()) != EOF && j != '#';) {
			if (isgraph(j)) {
				if (i < 5) wnext[i++] = j;
			} else if (i > 0) {
				wnext[i] = wnext[5] = '\0';
				add();
				i = 0;
			}
		}

		if (j == EOF) break;

		if (i > 0) {
			wnext[i] = wnext[5] = '\0';
			add();
		}

		while ((j = getchar()) != EOF && isgraph(j));

		j = hfree - 1;
		for (i = 0; i < j; i++)
			hnext[i] = i + 1;
		qsort(hnext, j, sizeof(hnext[0]), &cmp);

		printf("Set #%d:\n", t);
		for (i = 0; i < j; i++)
			printf("%s %d\n", hdata2[hnext[i]], hcount[hnext[i]]);
		printf("\n");
	}

	return 0;
}
