/*
ID: mjf28791
PROG: rect1
LANG: C
*/
#include <stdio.h>
#include <string.h>

#define MAXRECTS 131072
#define MAXCOL   4096

typedef struct {
	int x1, y1, x2, y2, c;
} rect_t;

static rect_t rect[MAXRECTS];
static int colors[MAXCOL], width, height;
static int prev[MAXRECTS], next[MAXRECTS], freelist;

static int add_c;

static void add(int x1, int y1, int x2, int y2)
{
	int t;

	t = freelist;
	freelist = next[freelist];

	next[t] = next[0];
	prev[t] = 0;
	prev[next[0]] = t;
	next[0] = t;

	rect[t].x1 = x1;
	rect[t].y1 = y1;
	rect[t].x2 = x2;
	rect[t].y2 = y2;
	rect[t].c = add_c;
}

static void split(rect_t *r, rect_t *s)
{
	add_c = r->c;

	if (r->x1 < s->x1) add(r->x1, r->y1, s->x1, r->y2);
	if (s->y2 < r->y2) add(s->x1, s->y2, s->x2, r->y2);
	if (s->x2 < r->x2) add(s->x2, r->y1, r->x2, r->y2);
	if (r->y1 < s->y1) add(s->x1, r->y1, s->x2, s->y1);
}

int main()
{
	static rect_t r, s;
	static int m, x1, y1, x2, y2, c;
	rect_t *p;
	int i;

	for (freelist = i = 1; i < MAXRECTS; i++)
		next[i] = i + 1;

	freopen("rect1.in", "r", stdin);
	freopen("rect1.out", "w", stdout);

	scanf("%d %d %d", &width, &height, &m);

	next[0] = 0;
	add_c = 1;
	add(0, 0, width, height);

	while (m-- > 0) {
		scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &c);
		r.x1 = x1;
		r.x2 = x2;
		r.y1 = y1;
		r.y2 = y2;
		r.c = c;

		for (i = next[0]; i != 0;) {
			p = &rect[i];

			s.x1 = (p->x1 > r.x1) ? p->x1 : r.x1;
			s.x2 = (p->x2 < r.x2) ? p->x2 : r.x2;
			if (s.x1 >= s.x2) {
				i = next[i];
				continue;
			}

			s.y1 = (p->y1 > r.y1) ? p->y1 : r.y1;
			s.y2 = (p->y2 < r.y2) ? p->y2 : r.y2;
			if (s.y1 >= s.y2) {
				i = next[i];
				continue;
			}

			split(p, &s);

			c = next[i];

			prev[next[i]] = prev[i];
			next[prev[i]] = next[i];

			next[i] = freelist;
			freelist = i;

			i = c;
		}

		add_c = r.c;
		add(r.x1, r.y1, r.x2, r.y2);
	}

	memset(colors, 0, sizeof(colors));
	for (i = next[0]; i != 0; i = next[i])
		colors[rect[i].c] += (rect[i].y2 - rect[i].y1) * (rect[i].x2 - rect[i].x1);

	for (i = 0; i < MAXCOL; i++)
		if (colors[i] != 0) printf("%d %d\n", i, colors[i]);

	return 0;
}
