#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int x, y;
} pt_t;

pt_t pt[16384];
int n;

int cmp(const void *a, const void *b)
{
	pt_t *p = (pt_t *)a, *q = (pt_t *)b;
	return (p->x != q->x) ? (p->x - q->x) : (p->y - q->y);
}

int find(int x, int y)
{
	int a, b, c;

	for (a = 0, b = n - 1; a <= b;) {
		c = (a + b) >> 1;

		if (pt[c].x == x && pt[c].y == y)
			return c;

		if (pt[c].x < x || (pt[c].x == x && pt[c].y < y))
			a = c + 1;
		else
			b = c - 1;
	}

	return -1;
}

int main()
{
	static int v[16384], t, sx, sy;
	int i, j;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (sx = sy = i = 0; i < n; i++) {
			scanf("%d %d", &pt[i].x, &pt[i].y);
			sx += pt[i].x;
			sy += pt[i].y;
		}

		if (((2 * sx) % n) != 0 || ((2 * sy) % n) != 0) {
			printf("no\n");
			continue;
		}

		sx = (2 * sx) / n;
		sy = (2 * sy) / n;

		qsort(pt, n, sizeof(pt[0]), &cmp);
		memset(v, 0, sizeof(v));

		for (i = 0; i < n; i++) {
			if (v[i])
				continue;

			if ((j = find(sx - pt[i].x, sy - pt[i].y)) < 0)
				break;

			v[i] = v[j] = 1;
		}

		printf((i < n) ? "no\n" : "yes\n");
	}

	return 0;
}
