#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
	char a[11], b[11];
} rec_t;

static rec_t *dict[100010];
static int nwords;

int cmp(const void *p, const void *q)
{
	return strcmp((*(rec_t **)p)->b, (*(rec_t **)q)->b);
}

static char *find(char *s)
{
	int a, b, c, t;

	for (a = 0, b = nwords - 1; a < b;) {
		c = (a + b) >> 1;

		t = strcmp(dict[c]->b, s);

		if (t == 0)
			return dict[c]->a;
		else if (t > 0)
			b = c - 1;
		else
			a = c + 1;
	}

	if (a == b && strcmp(dict[a]->b, s) == 0)
		return dict[a]->a;

	return NULL;
}

int main()
{
	static char buf[1024];
	int i;
	char *q;

	for (nwords = 0; gets(buf);) {
		for (i = 0; buf[i] && !isalpha(buf[i]); i++);
		if (buf[i] == '\0') break;

		dict[nwords] = (rec_t *)malloc(sizeof(rec_t));

		for (q = dict[nwords]->a; isalpha(buf[i]);)
			*q++ = buf[i++];
		*q = '\0';

		while (buf[i] && !isalpha(buf[i])) i++;

		for (q = dict[nwords]->b; isalpha(buf[i]);)
			*q++ = buf[i++];
		*q = '\0';

		nwords++;
	}

	qsort(dict, nwords, sizeof(rec_t *), cmp);

	while (gets(buf)) {
		q = find(buf);
		printf("%s\n", q ? q : "eh");
	}

	return 0;
}
