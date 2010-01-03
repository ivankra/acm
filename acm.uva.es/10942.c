#include <stdio.h>
#include <stdlib.h>

typedef struct { int y, m, d; } date;

int cmp(const void *pp, const void *qq)
{
	date *p = (date *)pp, *q = (date *)qq;
	if (p->y != q->y) return (p->y - q->y);
	if (p->m != q->m) return (p->m - q->m);
	return (p->d - q->d);
}

int valid(date t)
{
	static int a[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	a[2] = ((t.y % 400) == 0 || ((t.y % 4) == 0 && (t.y % 100) != 0)) ? 29 : 28;
	return (0 <= t.y && 1 <= t.m && t.m <= 12 && 1 <= t.d && t.d <= a[t.m]);
}

int main()
{
	date d[6];
	int i, t, c, x, y, z;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d %d %d", &c, &x, &y, &z) == 4;) {
		c %= 400;
		d[0].y = c * 100 + x; d[0].m = y; d[0].d = z;
		d[1].y = c * 100 + x; d[1].m = z; d[1].d = y;
		d[2].y = c * 100 + y; d[2].m = x; d[2].d = z;
		d[3].y = c * 100 + y; d[3].m = z; d[3].d = x;
		d[4].y = c * 100 + z; d[4].m = x; d[4].d = y;
		d[5].y = c * 100 + z; d[5].m = y; d[5].d = x;
		qsort(d, 6, sizeof(d[0]), &cmp);

		for (i = 0; i < 6 && !valid(d[i]); i++);
		if (i < 6)
			printf("%.2d %.2d %.2d\n", d[i].y % 100, d[i].m, d[i].d);
		else
			printf("-1\n");
	}

	return 0;
}
