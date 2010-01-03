#include <stdio.h>
#include <math.h>

#define EQ(x, y) ((((x) > (y)) ? ((x) - (y)) : ((y) - (x))) < 10e-9)

struct fig {
	int type;
	double x[3], y[3], r, r2;
	double minx, maxx, miny, maxy;
};

static int inside_r(struct fig *f, double x, double y)
{
	if (EQ(x, f->x[0]) || EQ(x, f->x[1])) return 0;
	if (EQ(y, f->y[0]) || EQ(y, f->y[1])) return 0;

	if (x < f->x[0] || x > f->x[1]) return 0;
	if (y > f->y[0] || y < f->y[1]) return 0;

	return 1;
}

static int inside_c(struct fig *f, double x, double y)
{
	double d2;

	d2 = (x - f->x[0]) * (x - f->x[0]) + (y - f->y[0]) * (y - f->y[0]);
	if (d2 > f->r2 || EQ(d2, f->r2)) return 0;

	return 1;
}

static int inside_t(struct fig *f, double x, double y)
{
	return 0;
}
int main()
{
	static struct fig f[128];
	double x, y;
	int i, c, n, t;

	for (n = 0; (c = getchar()) != EOF && (c != '*');) {
		if (c == 'r') {
			scanf("%lf%lf%lf%lf",
			      &f[n].x[0], &f[n].y[0], &f[n].x[1], &f[n].y[1]);
			f[n++].type = 'r';
		} else if (c == 'c') {
			scanf("%lf%lf%lf", &f[n].x[0], &f[n].y[0], &f[n].r);
			f[n].r2 = f[n].r * f[n].r;
			f[n++].type = 'c';
		} else if (c == 't') {
			scanf("%lf%lf%lf%lf%lf%lf", &f[n].x[0], &f[n].y[0],
			      &f[n].x[1], &f[n].y[1], &f[n].x[2], &f[n].y[2]);
			f[n++].type = 't';
		}
	}

	for (c = 1; scanf("%lf%lf", &x, &y) == 2; c++) {
		if (EQ(x, 9999.9) && EQ(y, 9999.9)) break;

		for (i = 0, t = 0; i < n; i++) {
			if ((f[i].type == 'r' && inside_r(&f[i], x, y)) ||
			    (f[i].type == 'c' && inside_c(&f[i], x, y)) ||
			    (f[i].type == 't' && inside_t(&f[i], x, y))) {
				printf("Point %d is contained in figure %d\n",
				       c, i + 1);
				t = 1;
			}
		}

		if (t == 0)
			printf("Point %d is not contained in any figure\n", c);
	}

	return 0;
}

