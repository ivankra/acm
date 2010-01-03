#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static char *lang1[2048], *lang2[2048];
static int l2mark[2048], n1, n2;

static int l2_exists(char *s, int mrk)
{
	int a, b, c, t;

	for (a = 0, b = n2 - 1; a <= b;) {
		c = (a + b) >> 1;
		t = strcmp(lang2[c], s);
		if (t < 0)
			a = c + 1;
		else if (t > 0)
			b = c - 1;
		else {
			if (l2mark[c] == mrk) return 0;
			l2mark[c] = mrk;
			return 1;
		}
	}
	
	return 0;
}

static int l2_pre(char *s, int mrk)
{
	int a, b, c, t, l;

	l = strlen(s);

	for (a = 0, b = n2 - 1; a <= b;) {
		c = (a + b) >> 1;
		t = strncmp(lang2[c], s, l);
		if (t < 0)
			a = c + 1;
		else if (t > 0)
			b = c - 1;
		else {
			a = b = c;
			break;
		}
	}

	if (a > b)
		return 0;

	t = 0;
	for (a = c - 1; a >= 0 && strncmp(lang2[a], s, l) == 0; a--)
		if (l2_exists(lang2[a] + l, mrk)) t++;

	for (; c < n2 && strncmp(lang2[c], s, l) == 0; c++)
		if (l2_exists(lang2[c] + l, mrk)) t++;

	return t;
}

static int solve()
{
	static char *pre[2048];
	int npre, i, j, r;
	char *p, *q;

	if (n1 == 0 || n2 == 0)
		return 0;

	memset(l2mark, 0, sizeof(l2mark));

	r = n1 * n2;

	pre[0] = lang1[0];
	npre = 1;

	for (i = 1; i < n1; i++) {
		for (j = 0; j < npre; j++) {
			for (p = pre[j], q = lang1[i]; *p == *q; p++, q++);
			if (*p == '\0')
				r -= l2_pre(q, i + 1);
			else
				break;
		}
		pre[j++] = lang1[i];
		npre = j;
	}

	return r;
}

int cmp(const void *p, const void *q)
{
	return strcmp(*(char **)p, *(char **)q);
}

int main()
{
	static char s[1024], l1buf[2048][16], l2buf[2048][16];
	int i, c, t;

	for (i = 0; i < 2048; i++) lang1[i] = l1buf[i];
	for (i = 0; i < 2048; i++) lang2[i] = l2buf[i];

	while (gets(s) && sscanf(s, "%d", &t) != 1);

	for (c = 1; c <= t; c++) {
		while (gets(s) && sscanf(s, "%d %d", &n1, &n2) != 2);

		for (i = 0; i < n1; i++)
			gets(lang1[i]);

		for (i = 0; i < n2; i++)
			gets(lang2[i]);

		qsort(lang1, n1, sizeof(lang1[0]), &cmp);
		qsort(lang2, n2, sizeof(lang2[0]), &cmp);

		printf("Case %d: %d\n", c, solve());
	}

	exit(0);
}
