#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define MAXN	2048
#define MAXS	65536
#define HDIV	65521

typedef struct {
	int src, dst, pref;
} rec_t;

char hbuf[1048576], *hptr, *hdata[MAXS];
unsigned crctab[256], htab[HDIV], hnext[MAXS], hcount;

int down[MAXS], nrec;
rec_t rec[MAXN];

int cmp(const void *p, const void *q)
{
	rec_t *a = (rec_t *)p, *b = (rec_t *)q;
	return (a->src != b->src) ? (a->src - b->src) : (a->pref - b->pref);
}

int lookup(char *s, int a)
{
	unsigned i, h;

	for (h = 0, i = 0; s[i]; i++)
		h = (h << 8) ^ crctab[h >> 24] ^ (unsigned)s[i];
	h %= HDIV;

	for (i = htab[h]; i != 0; i = hnext[i])
		if (strcmp(hdata[i], s) == 0) return i;

	if (a == 0) return 0;

	assert((hcount + 4) < MAXS);

	i = ++hcount;
	hdata[i] = hptr;
	do *hptr++ = *s; while (*s++ != '\0');
	hnext[i] = htab[h];
	htab[h] = i;
	return i;
}

void mkcrc()
{
	unsigned i, j, k;

	for (i = 0; i < 256; i++) {
		for (k = i << 24, j = 0; j < 8; j++)
			k = (k << 1) ^ ((k & 0x80000000) ? 0xEDB88320 : 0);
		crctab[i] = k;
	}
}

int find(int s)
{
	int a, b, c;

	for (a = 0, b = nrec - 1; a <= b;) {
		c = (a + b) >> 1;
		if (rec[c].src < s)
			a = c + 1;
		else if (rec[c].src > s)
			b = c - 1;
		else
			return c;
	}

	return -1;
}

void process(char *s)
{
	static char t[1024];
	int i, j, k, m, rdst, rpref;

	rdst = 0;
	rpref = 0x7FFFFFFF;

	for (i = -1; i < 0 || s[i]; i++) {
		if (i < 0) {
			strcpy(t, s);
		} else {
			if (s[i] != '.') continue;
			sprintf(t, "*%s", s + i);
		}

		k = lookup(t, 0);
		if (k <= 0) continue;

		m = find(k);
		if (m < 0) continue;

		for (j = m; j >= 0 && rec[j].src == k; j--)
			if (!down[rec[j].dst] && rec[j].pref < rpref) {
				rdst = rec[j].dst;
				rpref = rec[j].pref;
			}

		for (j = m + 1; j < nrec && rec[j].src == k; j++)
			if (!down[rec[j].dst] && rec[j].pref < rpref) {
				rdst = rec[j].dst;
				rpref = rec[j].pref;
			}
	}

	if (rdst > 0)
		printf("%s => %s\n", s, hdata[rdst]);
	else
		printf("%s =>\n", s);
}

int main()
{
	static char s1[1024], s2[1024], s3[1024];
	int i;

	while (gets(s1) && sscanf(s1, "%d", &nrec) != 1);
	assert(nrec < MAXN);

	mkcrc();
	hcount = 0;
	hptr = hbuf;
	memset(htab, 0, sizeof(htab));

	for (i = 0; i < nrec && gets(s1); i++) {
		if (!isspace(s1[0]) || i == 0) {
			sscanf(s1, " %s %d %s", s2, &rec[i].pref, s3);
			rec[i].src = lookup(s2, 1);
			rec[i].dst = lookup(s3, 1);
		} else {
			sscanf(s1, " %d %s", &rec[i].pref, s3);
			rec[i].src = rec[i - 1].src;
			rec[i].dst = lookup(s3, 1);
		}
	}

	qsort(rec, nrec, sizeof(rec[0]), &cmp);

	memset(down, 0, sizeof(down));

	while (gets(s1)) {
		sscanf(s1, " %s %s", s2, s3);

		s2[0] = toupper(s2[0]);
		if (s2[0] == 'X') {
			break;
		} else if (s2[0] == 'U') {
			i = lookup(s3, 0);
			if (i > 0) down[i] = 0;
		} else if (s2[0] == 'D') {
			i = lookup(s3, 0);
			if (i > 0) down[i] = 1;
		} else if (s2[0] == 'A') {
			process(s3);
		}
	}

	return 0;
}
