#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int w, s;
} turtle_t;

int cmp(const void *p, const void *q)
{
	turtle_t *a = (turtle_t *)p, *b = (turtle_t *)q;
	return (a->s != b->s) ? (a->s - b->s) : (a->w - b->w);
}

int main()
{
	static turtle_t a[8192];
	static int z[2][8192];
	int i, j, k, r, n, *tab, *next;

	for (n = 0; scanf("%d %d", &a[n].w, &a[n].s) == 2;)
		if (a[n].w <= a[n].s) n++;

	qsort(a, n, sizeof(a[0]), &cmp);

	tab = z[0];
	tab[0] = 0;
	r = 0;

	for (i = 0; i < n; tab = next, i++) {
		next = (tab == z[0]) ? z[1] : z[0];

		next[0] = 0;
		for (j = 1; j <= r; j++) {
			k = tab[j - 1] + a[i].w;
			if (k <= a[i].s && k <= tab[j])
				next[j] = k;
			else
				next[j] = tab[j];
		}

		if ((tab[r] + a[i].w) <= a[i].s) {
			next[r + 1] = tab[r] + a[i].w;
			r++;
		}
	}

	printf("%d\n", r);
	return 0;
}
