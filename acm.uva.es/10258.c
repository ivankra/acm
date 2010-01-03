#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int id, t, n, s, a[16];
} rec_t;

int cmp(const void *p, const void *q)
{
	rec_t *a = (rec_t *)p, *b = (rec_t *)q;
	if (a->n != b->n) return (b->n - a->n);
	if (a->t != b->t) return (a->t - b->t);
	return (a->id - b->id);
}

int main()
{
	static rec_t r[128];
	static char s[1024], c;
	int i, t, id, p, tm;

	while (gets(s) && sscanf(s, "%d", &t) != 1);
	gets(s);

	while (t-- > 0) {
		memset(r, 0, sizeof(r));
		for (i = 1; i <= 100; i++)
			r[i].id = i;

		while (gets(s) && sscanf(s, "%d %d %d %c", &id, &p, &tm, &c) == 4) {
			if (id < 1 || id > 100) continue;
			if (p < 1 || p > 9) continue;

			if (c == 'C' || c == 'c') {
				if (r[id].a[p] < 0) continue;
				r[id].t += tm + 20 * r[id].a[p];
				r[id].n++;
				r[id].a[p] = -1;
			} else if (c == 'I' || c == 'i') {
				if (r[id].a[p] < 0) continue;
				r[id].a[p]++;
			}
			r[id].s++;
		}

		qsort(&r[1], 100, sizeof(r[1]), &cmp);

		for (i = 1; i <= 100; i++)
			if (r[i].s > 0)
				printf("%d %d %d\n", r[i].id, r[i].n, r[i].t);
		if (t) printf("\n");
	}

	return 0;
}
