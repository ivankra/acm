/*
ID: mjf28791
PROG: milk2
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int a, b;
} rec_t;

int cmp(const void *p, const void *q)
{
	rec_t *x = (rec_t *)p, *y = (rec_t *)q;
	return (x->a != y->a) ? (x->a - y->a) : (x->b - y->b);
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int main()
{
	static rec_t r[8196];
	int i, n, s, t, x, y;

	freopen("milk2.in", "r", stdin);
	freopen("milk2.out", "w", stdout);

	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d %d", &r[i].a, &r[i].b);

	qsort(r, n, sizeof(rec_t), &cmp);

	for (x = y = i = 0, s = t = r[0].a; i < n; i++) {
		if (r[i].a > t) {
			y = max(y, r[i].a - t);
			s = t = r[i].a;
		}

		t = max(t, r[i].b);
		x = max(x, t - s);
	}

	printf("%d %d\n", x, y);
	return 0;
}
