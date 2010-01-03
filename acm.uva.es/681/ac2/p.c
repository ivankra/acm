#include <stdio.h>
#include <stdlib.h>

typedef struct { int x, y; } pt;

int cmp(const void *pp, const void *qq)
{
	pt *p = (pt *)pp, *q = (pt *)qq;
	return (p->y != q->y) ? (p->y - q->y) : (p->x - q->x);
}

int dir(pt *a, pt *b, pt *c)
{
	return (b->x - a->x) * (c->y - a->y) + (a->x - c->x) * (b->y - a->y);
}

int hull(int h[], pt a[], int n)
{
	int i, s, t;

	qsort(a, n, sizeof(pt), &cmp);

	if (n <= 1) {
		h[0] = 0;
		return n;
	}

	for (h[0] = 0, s = 1, i = 1; i < n; i++) {
		while (s >= 2 && dir(&a[h[s-2]], &a[h[s-1]], &a[i]) <= 0) s--;
		h[s++] = i;
	}

	for (t = s, i = n - 2; i >= 0; i--) {
		while (s >= (t + 1) && dir(&a[h[s-2]], &a[h[s-1]], &a[i]) <= 0) s--;
		h[s++] = i;
	}

	return s;
}

int main()
{
	static pt a[1024];
	static int h[2048];
	int i, n, t;

	scanf("%d", &t);
	printf("%d\n", t);

	while (t-- > 0 && scanf("%d", &n) == 1) {
		for (i = 0; i < n; i++)
			scanf("%d %d", &a[i].x, &a[i].y);
		scanf("%*d");

		n = hull(h, a, n);

		printf("%d\n", n);
		for (i = 0; i < n; i++)
			printf("%d %d\n", a[h[i]].x, a[h[i]].y);

		if (t > 0) printf("-1\n");
	}

	return 0;
}
