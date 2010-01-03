#include <stdio.h>
#include <string.h>

#define INF 0x3FFFFFFF

int adj[65536], cap[65536], ref[65536], back[65536], next[65536], adjn;
int match[65536], nvert, testno;

char strbuf[131072], *strbufp, *vertname[4096];
unsigned crctab[256];

struct htab {
	int n;
	char *name[65536];
	int vert[65536], tab[65521], got[65521], hnext[65536];
} citizens, parties, clubs;

int find()
{
	static int id = 1, v[65536], p[65536], s[65536], t;
	int i, j;

	for (v[s[0] = 0] = ++id, t = 1; t > 0 && v[1] != id;)
		for (j = adj[i = s[--t]]; j; j = next[j])
			if (cap[j] > 0 && v[ref[j]] != id)
				v[s[t++] = ref[j]] = id, p[ref[j]] = j;

	if (v[1] != id)
		return 0;

	for (i = 1; i != 0; i = ref[back[p[i]]]) {
		cap[p[i]]--;
		cap[back[p[i]]]++;
	}

	return 1;
}

void mkcrc()
{
	unsigned i, j, t;
	for (i = 0; i < 256; i++) {
		for (t = i << 24, j = 0; j < 8; j++)
			t = (t << 1) ^ ((t & 0x80000000) ? 0xEDB88320 : 0);
		crctab[i] = t;
	}
}

char *stradd(char *s)
{
	char *r = strbufp;
	do *strbufp++ = *s; while (*s++);
	return r;
}

int lookup(struct htab *p, char *s)
{
	unsigned h;
	int i;

	if (p == &citizens) {
		i = ++(p->n);
	} else {
		for (i = h = 0; s[i]; i++)
			h = (h << 8) ^ crctab[h >> 24] ^ ((unsigned char *)s)[i];
		h %= 65521;

		if (p->got[h] == testno) {
			for (i = p->tab[h]; i; i = p->hnext[i])
				if (strcmp(p->name[i], s) == 0)
					return p->vert[i];
			i = ++(p->n);
			p->hnext[i] = p->tab[h];
		} else {
			i = ++(p->n);
			p->got[h] = testno;
			p->hnext[i] = 0;
		}
		p->tab[h] = i;
	}

	p->name[i] = stradd(s);
	p->vert[i] = nvert;
	adj[nvert] = 0;
	vertname[nvert++] = p->name[i];
	return p->vert[i];
}

void add(int u, int v, int c)
{
	int p, q;

	p = ++adjn;
	q = ++adjn;

	ref[p] = v;
	next[p] = adj[u];
	adj[u] = p;
	cap[p] = c;
	back[p] = q;

	ref[q] = u;
	next[q] = adj[v];
	adj[v] = q;
	cap[q] = 0;
	back[q] = p;
}

int main()
{
	static char s[1024], s1[1024], s2[1024];
	int i, j, t, p, q;

	while (gets(s) && sscanf(s, "%d", &t) != 1);
	gets(s);

	mkcrc();

	for (testno = 1; testno <= t; testno++) {
		if (testno > 1) printf("\n");

		nvert = 2;
		adj[0] = adj[1] = adjn = 0;
		strbufp = strbuf;

		citizens.n = parties.n = clubs.n = 0;

		while (gets(s) && sscanf(s, " %s %s%n", s1, s2, &q) >= 2) {
			i = lookup(&citizens, s1);
			add(lookup(&parties, s2), i, 1);
			for (p = q; sscanf(s + p, " %s%n", s2, &q) >= 1; p += q)
				add(i, lookup(&clubs, s2), 1);
		}

		if (clubs.n > citizens.n || parties.n < 3) {
			printf("Impossible.\n");
			continue;
		}

		p = clubs.n ? ((clubs.n - 1) >> 1) : 0;
		for (i = 1; i <= parties.n; i++)
			add(0, parties.vert[i], p);

		for (i = 1; i <= clubs.n; i++)
			add(clubs.vert[i], 1, 1);

		for (i = 0; find(); i++);
		if (i != clubs.n) {
			printf("Impossible.\n");
			continue;
		}

		for (i = 1; i <= clubs.n; i++)
			for (j = adj[clubs.vert[i]]; j; j = next[j])
				if (ref[j] > 1 && cap[j] > 0) {
					printf("%s %s\n", vertname[ref[j]], clubs.name[i]);
					break;
				}

	}

	return 0;
}
