#include <stdio.h>
#include <stdlib.h>

typedef struct { int x, y; } pt_t;
pt_t p[100001];
int n;

int cmp(const void *p, const void *q)
{
	pt_t *a = (pt_t *)p, *b = (pt_t *)q;
	int k = (a->x - a->y) - (b->x - b->y);
	return (k != 0) ? k : 0;
}

int check(int t)
{
	int i, j, k, u;

printf("check(t=%d):\n",t);
for (i = 0; i < n; i++)
	printf("[%d,%d]\n", p[i].x-p[i].y+t, p[i].x+p[i].y-t);
printf("\n");

	for (i = k = 0, u = -0x3FFFFFFF;; k++) {
		while (i < n && (p[i].x - p[i].y + t) <= u) i++;
		if (i >= n) break;

		j = p[i].x - p[i].y + t;
		u = p[i].x + p[i].y - t;
		for (i++; i < n && (p[i].x - p[i].y + t) == j; i++)
			if ((p[i].x + p[i].y - t) < u) u = p[i].x + p[i].y - t;
	}

	return k;
}

int main()
{
	int a, b, i, m, s, t;

	for (scanf("%d", &t), s = 1; s <= t && scanf("%d %d", &n, &m) == 2; s++) {
		for (i = 0; i < n; i++)
			scanf("%d %d", &p[i].y, &p[i].x);
		qsort(p, n, sizeof(p[0]), &cmp);

		for (a = p[i = 0].y; i < n; i++)
			if (p[i].y < a) a = p[i].y;
/*		b = (p[0].x + p[0].y - p[n-1].x + p[n-1].y) / 2 - 10;*/
		b = -10000000;

printf("a=%d b=%d m=%d\n",a,b,m);
printf("f(a)=%d\n",check(a));
break;

		while (a > b) {
			i = (a + b + 1) / 2;
			if (check(i) > m)
				a = i - 1;
			else
				b = i;
		}

		printf("Case %d: %d\n", s, a);
	}

	return 0;
}
