#include <stdio.h>

typedef struct { int x, y; } pt_t;
typedef struct { int xmin, xmax, ymin, ymax; } rect_t;
typedef struct { pt_t a, b; } line_t;

void order(int *x, int *y)
{
	int t;

	if (*x > *y) {
		t = *x;
		*x = *y;
		*y = t;
	}
}


int inside(pt_t p, rect_t r)
{
	return (r.xmin <= p.x && p.x <= r.xmax) && (r.ymin <= p.y && p.y <= r.ymax);
}

line_t ltrans(line_t l, int dx, int dy)
{
	line_t r;
	r.a.x = l.a.x + dx;
	r.a.y = l.a.y + dy;
	r.b.x = l.b.x + dx;
	r.b.y = l.b.y + dy;
	return r;
}

line_t lswap(line_t l)
{
	line_t r;
	r.a = l.b;
	r.b = l.a;
	return r;
}

int xinter(line_t l, int h)
{
	int t;

	if (l.a.x < 0 && l.b.x < 0) return 0;
	if (l.a.x > h && l.b.x > h) return 0;

	if (l.a.y > 0 && l.b.y > 0) return 0;
	if (l.a.y < 0 && l.b.y < 0) return 0;

	if (l.a.y == l.b.y)
		return (l.a.y == 0);

	if (l.a.x == l.b.x)
		return 1;

	if (l.a.y < l.b.y)
		return xinter(lswap(l), h);

	t = -l.a.y * (l.a.x - l.b.x) + l.a.x * (l.a.y - l.b.y);
	if (0 <= t && t <= (h * (l.a.y - l.b.y)))
		return 1;

	return 0;
}

int yinter(line_t l, int h)
{
	line_t m;

	m.a.x = l.a.y;
	m.a.y = -l.a.x;
	m.b.x = l.b.y;
	m.b.y = -l.b.x;

	return xinter(m, h);
}

int main()
{
	rect_t r;
	line_t l;
	int t;

	scanf("%d", &t);
	while (t-- > 0) {
		scanf("%d %d %d %d %d %d %d %d",
			&l.a.x, &l.a.y, &l.b.x, &l.b.y,
			&r.xmin, &r.ymin, &r.xmax, &r.ymax);

		order(&r.xmin, &r.xmax);
		order(&r.ymin, &r.ymax);

		if (inside(l.a, r) || inside(l.b, r)) {
			printf("T\n");
			continue;
		}

		if (xinter(ltrans(l, -r.xmin, -r.ymax), r.xmax - r.xmin) ||
		    xinter(ltrans(l, -r.xmin, -r.ymin), r.xmax - r.xmin) ||
		    yinter(ltrans(l, -r.xmin, -r.ymin), r.ymax - r.ymin) ||
		    yinter(ltrans(l, -r.xmax, -r.ymin), r.ymax - r.ymin)) {
			printf("T\n");
			continue;
		}

		printf("F\n");
	}

	return 0;
}
