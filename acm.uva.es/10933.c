#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct { char nam[32]; int won, sets, pt; } team_t;
team_t a[1024];
int n;

char buf[65536], s1[1024], s2[1024];

int cmp(const void *pp, const void *qq)
{
	team_t *p = (team_t *)pp, *q = (team_t *)qq;
	if (p->won != q->won) return (q->won - p->won);
	if (p->sets != q->sets) return (q->sets - p->sets);
	if (p->pt != q->pt) return (q->pt - p->pt);
	return strcmp(p->nam, q->nam);
}

int what(char *s)
{
	int i;
	for (i = 0; i < n; i++) if (strcmp(a[i].nam, s) == 0) return i;
	abort();
}

int main()
{
	int i, j, k, p, q, x, y, m;

	for (;;) {
		for (;;) {
			if (gets(buf) == NULL) return 0;
			if (sscanf(buf, "%d", &n) == 1) break;
		}
		if (n == 0) break;

		for (i = 0; i < n; i++) {
			gets(a[i].nam);
			a[i].won = a[i].sets = a[i].pt = 0;
		}

		while (gets(buf) && sscanf(buf, "%d", &m) != 1);

		while (m-- > 0 && gets(buf)) {
			sscanf(buf, "%[^-]-%[^:]:%n", s1, s2, &p);
			i = what(s1); j = what(s2); k = 0;
			while (sscanf(buf+p, " %d - %d%n", &x, &y, &q) >= 2) {
				p += q;
				if (x > y) { k++; }
				if (y > x) { k--; }
				a[i].pt += x; a[j].pt += y;
			}
			a[i].sets += k; a[j].sets -= k;
			if (k > 0) a[i].won++;
			if (k < 0) a[j].won++;
		}

		qsort(a, n, sizeof(a[0]), &cmp);

		for (i = 0; i < n; i++)
			printf("%-20s%5d%5d%10d\n", a[i].nam, a[i].won, a[i].sets, a[i].pt);
		printf("\n");
	}

	return 0;
}
