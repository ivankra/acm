#include <stdio.h>
#include <string.h>

#define HDIV 261959
#define HSIZE 2250010

int htab[HDIV], hnext[HSIZE], count;
char *hword1[HSIZE], *hword2[HSIZE], wbuf[65536], *wnext;

int hash(char *s)
{
	unsigned h;

	for (h = 0; *s; s++) {
		h = h * 31 + *s - 'a';
		if (h > HDIV) h %= HDIV;
	}

	return h;
}

void hadd(char *w1, char *w2)
{
	static char s[1024], t[1024];
	int i, h;

	sprintf(s, "%s%s", w1, w2);

	h = hash(s);
	for (i = htab[h]; i != 0; i = hnext[i]) {
		sprintf(t, "%s%s", hword1[i], hword2[i]);
		if (strcmp(s, t) == 0) return;
	}

	i = ++count;
	hword1[i] = w1;
	hword2[i] = w2;
	hnext[i] = htab[h];
	htab[h] = i;
}

char *wadd(char *s)
{
	char *r;

	r = wnext;
	while (*s)
		*wnext++ = *s++;
	*wnext++ = '\0';

	return r;
}

int solve()
{
	static char s[1024], *lang1[2048], *lang2[2048];
	int i, j, n1, n2;

	wnext = wbuf;

	while (gets(s) && sscanf(s, "%d %d", &n1, &n2) != 2);

	for (i = 0; i < n1 && gets(s); i++)
		lang1[i] = wadd(s);

	for (i = 0; i < n2 && gets(s); i++)
		lang2[i] = wadd(s);

	memset(htab, 0, sizeof(htab));
	count = 0;

	for (i = 0; i < n1; i++)
		for (j = 0; j < n2; j++)
			hadd(lang1[i], lang2[j]);

	return count;
}

int main()
{
	char s[1024];
	int t, c;

	while (gets(s) && sscanf(s, "%d", &t) != 1);

	for (c = 1; c <= t; c++)
		printf("Case %d: %d\n", c, solve());

	return 0;
}
