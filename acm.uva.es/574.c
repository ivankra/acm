#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct rec {
	int k;
	int a[16];
};

int cmp(const void *pp, const void *pq)
{
	struct rec *p, *q;
	int i, n;

	p = (struct rec *)pp;
	q = (struct rec *)pq;

	n = (p->k <= q->k) ? p->k : q->k;
	for (i = 0; i < n; i++)
		if (p->a[i] != q->a[i])
			return (p->a[i] > q->a[i]) ? -1 : 1;

	return 0;
}

int main()
{
	static int t, n, a[16];
	static struct rec r[4096];
	int i, k, m, c, j;

	while (scanf("%d %d", &t, &n) == 2 && t > 0 && n > 0) {
		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);

		printf("Sums of %d:\n", t);
		for (c = 0, m = 1; (m >> n) == 0; m++) {
			for (k = 0, i = 0; i < n; i++)
				if ((m >> i) & 1) k += a[i];
			if (k != t) continue;

			for (i = 0, k = 0; i < n; i++)
				if ((m >> i) & 1)
					r[c].a[k++] = a[i];
			r[c++].k = k;				
		}

		if (c == 0)
			printf("NONE\n");

		if (c > 1)
			qsort((void *)r, c, sizeof(struct rec), cmp);

		for (i = 0; i < c; i++) {
			if (i >= 1 && r[i - 1].k == r[i].k) {
				for (j = 0; j < r[i].k; j++)
					if (r[i - 1].a[j] != r[i].a[j]) break;
				if (j >= r[i].k) continue;
			}

			for (j = 0; j < r[i].k; j++)
				printf(j ? "+%d" : "%d", r[i].a[j]);
			printf("\n");
		}
	}

	return 0;
}
