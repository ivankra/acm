#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct {
	int n, w[16];
} tit[1024];

char wbuf[1048576], *words[65536];
int nwords, nignore, ntit, nlist;

typedef struct {
	int k, t;
} list_t;

list_t list[65536];

int get(char *s)
{
	int i;

	for (i = 0; i < nwords; i++)
		if (strcmp(words[i], s) == 0) return i;

	strcpy(words[nwords], s);
	words[nwords + 1] = words[nwords] + strlen(s) + 1;
	return nwords++;
}

void parse(char *s)
{
	static char t[65536];
	int k, m;

	m = ntit++;
	tit[m].n = 0;

	for (;;) {
		while (*s && !isalpha(*s)) s++;
		if (*s == '\0') break;

		for (k = 0; *s && isalpha(*s); s++)
			t[k++] = tolower(*s);
		t[k] = '\0';

		tit[m].w[tit[m].n++] = get(t);
	}

	for (k = 0; k < tit[m].n; k++) {
		if (tit[m].w[k] >= nignore) {
			list[nlist].k = k;
			list[nlist++].t = m;
		}
	}
}

int cmp(const void *p, const void *q)
{
	list_t *a = (list_t *)p, *b = (list_t *)q;

	if (tit[a->t].w[a->k] != tit[b->t].w[b->k])
		return strcmp(words[tit[a->t].w[a->k]], words[tit[b->t].w[b->k]]);

	return (a->t - b->t);
}

void print(list_t *p)
{
	int i;
	char *s;

	for (i = 0; i < tit[p->t].n; i++) {
		if (i != 0)
			putchar(' ');

		s = words[tit[p->t].w[i]];

		if (i == p->k)
			while (*s) putchar(toupper(*s++));
		else
			printf("%s", s);
	}

	putchar('\n');
}

int main()
{
	static char s[65536];
	int i;

	words[nwords = 0] = wbuf;

	while (scanf(" %s", s) == 1 && s[0] != ':') {
		for (i = 0; s[i]; i++) s[i] = tolower(s[i]);
		get(s);
	}

	nignore = nwords;
	nlist = 0;
	ntit = 0;

	while (gets(s))
		parse(s);

	qsort(list, nlist, sizeof(list[0]), &cmp);

	for (i = 0; i < nlist; i++)
		print(&list[i]);

	return 0;
}
