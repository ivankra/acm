#include <stdio.h>
#include <string.h>

typedef struct {
	int x1, y1, x2, y2, c, area;
} rect_t;

int nrect;
rect_t rect[1024];

void addrect(int x1, int y1, int x2, int y2, int c)
{
	if (x1 > x2) return;
	if (y1 > y2) return;
	rect[nrect].x1 = x1;
	rect[nrect].y1 = y1;
	rect[nrect].x2 = x2;
	rect[nrect].y2 = y2;
	rect[nrect].c = c;
	nrect++;
}

int min(int a, int b)
{
	return (a < b) ? a : b;
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int isect(rect_t *r, rect_t *a, rect_t *b)
{
	r->x1 = max(a->x1, b->x1);
	r->x2 = min(a->x2, b->x2);
	r->y1 = max(a->y1, b->y1);
	r->y2 = min(a->y2, b->y2);
	return ((r->x1 <= r->x2) && (r->y1 <= r->y2));
}

int adj(int a, int b)
{
	int dx, dy;

	dx = min(rect[a].x2, rect[b].x2) - max(rect[a].x1, rect[b].x1) + 1;
	dy = min(rect[a].y2, rect[b].y2) - max(rect[a].y1, rect[b].y1) + 1;

	return ((dx == 0 && dy > 0) || (dy == 0 && dx > 0));
}

void split(rect_t *r, rect_t *s)
{
	addrect(r->x1, r->y1, r->x2, s->y1 - 1, r->c);
	addrect(r->x1, s->y2 + 1, r->x2, r->y2, r->c);
	addrect(r->x1, s->y1, s->x1 - 1, s->y2, r->c);
	addrect(s->x2 + 1, s->y1, r->x2, s->y2, r->c);
}

void add(int x1, int y1, int x2, int y2, int m)
{
	rect_t s, r;
	int i;

	r.x1 = x1;
	r.y1 = y1;
	r.x2 = x2;
	r.y2 = y2;

	for (i = nrect - 1; i >= 0; i--) {
		if (!isect(&s, &rect[i], &r))
			continue;

		split(&rect[i], &s);

		rect[i].x1 = s.x1;
		rect[i].x2 = s.x2;
		rect[i].y1 = s.y1;
		rect[i].y2 = s.y2;
		rect[i].c |= (1 << m);
	}
}

int query(int x, int y)
{
	static int s[1024], u[1024];
	int i, t, area;;

	for (i = 0; i < nrect; i++)
		u[i] = 0;

	for (i = 0; i < nrect; i++)
		if (rect[i].x1 <= x && x <= rect[i].x2 &&
		    rect[i].y1 <= y && y <= rect[i].y2)
			break;

	if (i >= nrect)
		return 0;

	for (area = 0, s[0] = i, u[i] = 1, t = 1; t > 0;) {
		x = s[--t];
		area += rect[x].area;

		for (y = 0; y < nrect; y++)
			if (u[y] == 0 && rect[x].c == rect[y].c && adj(x, y))
				u[s[t++] = y] = 1;
	}

	return area;
}

int main()
{
	int i, m, t, x1, y1, s;

	for (t = 1; scanf("%d", &m) == 1; t++) {
		nrect = 0;
		addrect(1, 1, 10000, 10000, 0);

		for (i = 0; i < m; i++) {
			scanf("%d %d %d", &x1, &y1, &s);
			add(x1, y1, x1 + s - 1, y1 + s - 1, i);
		}

		for (i = 0; i < nrect; i++)
			rect[i].area = (rect[i].x2 - rect[i].x1 + 1) * (rect[i].y2 - rect[i].y1 + 1);

		printf("Case %d:\n", t);
		for (scanf("%d", &m); m-- > 0 && scanf("%d %d", &x1, &y1);)
			printf("%d\n", query(x1, y1));
	}

	return 0;
}
