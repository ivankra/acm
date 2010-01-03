#include <stdio.h>
#include <string.h>

#define DIV	131063
#define ASIZE	1048576

struct {
	int next, adj;
	char s[32];
} tab[32768];

int htab[DIV], hsize;
int adj_ref[ASIZE], adj_next[ASIZE], asize;

int hash(char *s)
{
	unsigned r;

	for (r = 0; *s;) {
		r = r * 26 + *s++ - 'a';
		if (r >= DIV) r %= DIV;
	}

	return r;
}

int lookup(char *s)
{
	int p;

	for (p = htab[hash(s)]; p != 0; p = tab[p].next)
		if (strcmp(tab[p].s, s) == 0) return p;

	return 0;
}

int add(char *s)
{
	int h = hash(s);
	hsize++;
	strcpy(tab[hsize].s, s);
	tab[hsize].adj = 0;
	tab[hsize].next = htab[h];
	htab[h] = hsize;
	return hsize;
}

void make_adj()
{
	static char s[1024];
	int i, j, k;

	asize = 0;

	for (k = 1; k <= hsize; k++) {
		strcpy(s, tab[k].s);

		for (i = 0; s[i]; i++) {
			for (s[i] = 'a'; s[i] <= 'z'; s[i]++) {
				if (s[i] == tab[k].s[i])
					continue;

				j = lookup(s);
				if (j == 0)
					continue;

				asize++;
				adj_ref[asize] = j;
				adj_next[asize] = tab[k].adj;
				tab[k].adj = asize;
			}
			s[i] = tab[k].s[i];
		}
	}
}

int solve(int src, int dst)
{
	static int p[32768], q[32768], h, t;
	int i, j, k;

	if (strlen(tab[src].s) != strlen(tab[dst].s))
		return 1;

	for (i = 0; i <= hsize; i++)
		p[i] = 0;

	h = t = 0;
	p[q[t++] = dst] = dst;

	while (h < t && p[src] == 0)
		for (j = tab[i = q[h++]].adj; j != 0; j = adj_next[j])
			if (p[k = adj_ref[j]] == 0) p[q[t++] = k] = i;

	if (p[src] == 0)
		return 1;

	for (i = src; i != dst; i = p[i])
		printf("%s\n", tab[i].s);
	printf("%s\n", tab[dst].s);

	return 0;
}

int main()
{
	static char s[1024], t[1024];
	int x, y, z;

	memset(htab, 0, sizeof(htab));
	for (hsize = 0; gets(s) && sscanf(s, " %[a-z]", t) == 1;)
		if (lookup(t) == 0) add(t);

	make_adj();

	for (z = 0; scanf(" %s %s", s, t) == 2;) {
		if (z++ != 0)
			printf("\n");

		x = lookup(s);
		y = lookup(t);

		if (x == 0 || y == 0 || solve(x, y))
			printf("No solution.\n");
	}

	return 0;
}
