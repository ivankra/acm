#include <stdio.h>
#include <stdlib.h>

#define INF 0x1FFFFFFF

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

	for (i = k = 0, u = -INF;;) {
		while (i < n && (p[i].x - p[i].y + t) <= u) i++;
		if (i >= n) break;
		u = p[i].x + p[i].y - t;
		k++;
	}

printf("<<%d>>\n\n",k);

}

/*
(x,y) -> [x-y+t,x+y-t],t

                                                           (x',y')
projection of (x,y) onto y=t:                (x,y)       /
L = x + (t - y) = x - y + t                /       \   /
R = x - (t - y) = x + y - t       --y=t--L-----------R-------
                                                     L'
t fixed;

R = (x+y) - t
R = (x'-y') + t

2R - (x+y) = (x'-y')

*/


int main()
{
	int i, c, t, m;

	for (scanf("%d", &t), c = 1; c <= t && scanf("%d %d", &n, &m); c++) {
		for (i = 0; i < n; i++)
			scanf("%d %d", &p[i].y, &p[i].x);
		qsort(p, n, sizeof(p[0]), &cmp);

		check(-2);
		check(-1);
break;
	}

	return 0;
}
