#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct { int x, y; } pt;

pt px[1024], py[1024];
int n;

int cmpx(const void *p, const void *q)
{
	return ((pt *)p)->x - ((pt *)q)->x;
}

int cmpy(const void *p, const void *q)
{
	return ((pt *)p)->y - ((pt *)q)->y;
}

int find(int y, int s)
{
	int i, r, t;

	for (r = 0, i = 0;;) {
		px[n].y = y;
		while (px[i].y != y) i++;
		if (i >= n) return r;

		t = px[i].x;
		px[n].x = t + 1;
		while (px[i].x == t) i++;

		r++;
		y += s;
		s = -s;
	}
}

int main()
{
	int i, t, r;

	while (scanf("%d", &n) == 1) {
		for (i = 0; i < n; i++) {
			scanf("%d %d", &px[i].x, &px[i].y);
			py[i].x = px[i].x;
			py[i].y = px[i].y;
		}

		qsort(px, n, sizeof(px[0]), &cmpx);
		qsort(py, n, sizeof(py[0]), &cmpy);

		for (r = 0, i = 0; i < n; i++) {
			if (i == 0 || py[i - 1].y != py[i].y) {
				if ((t = find(py[i].y, 2)) > r) r = t;
				if ((t = find(py[i].y, -2)) > r) r = t;
			}
		}

		printf("%d\n", r);
	}

	return 0;
}
