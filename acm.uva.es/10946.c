#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct { int a, c; } hole_t;

int map[64][64], n, m;

int go(int y, int x, int c)
{
	if (map[y][x] != c) return 0;
	map[y][x] = '.';
	return (1 + go(y-1,x,c) + go(y+1,x,c) + go(y,x-1,c) + go(y,x+1,c));
}

int cmp(const void *pp, const void *qq)
{
	hole_t *p = (hole_t *)pp, *q = (hole_t *)qq;
	if (p->c != q->c) return q->c - p->c;
	return (p->a - q->a);
}

int main()
{
	static hole_t h[65536];
	int i, j, k, c, t;

	for (t = 1; scanf("%d %d", &n, &m) == 2 && n > 0; t++) {
		for (i = 0; i < 26; i++) {
			h[i].a = 'A'+i;
			h[i].c = 0;
		}

		memset(map, 0, sizeof(map));

		for (i = 1; i <= n; i++)
			for (j = 1; j <= m && (k = getchar()) != EOF;)
				if (('A' <= k && k <= 'Z') || (k == '.'))
					map[i][j++] = k;

		k = 0;
		for (i = 1; i <= n; i++)
			for (j = 1; j <= m; j++)
				if (map[i][j] != '.') {
					h[k].a = map[i][j];
					h[k].c = go(i,j,h[k].a);
					k++;
				}

		qsort(h, k, sizeof(h[0]), &cmp);

		printf("Problem %d:\n", t);
		for (i = 0; i < k; i++)
			printf("%c %d\n", h[i].a, h[i].c);
	}

	return 0;
}
