#include <stdio.h>
#include <math.h>

#define EQ(x, y) ((((x) > (y)) ? ((x) - (y)) : ((y) - (x))) < 10e-9)

struct fig {
	int type;
	double x[4], y[4], r, r2;
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
	double t;
	int i, k, m;

	for (i = 0; i < 3; i++)
		if (EQ(f->x[i], x) && EQ(f->y[i], y)) return 0;

	for (i = 0; i < 3; i++)
		if (EQ(f->x[i], x)) break;

	if (i < 3) {
		k = (i + 2) % 3;
		m = (i + 1) % 3;

		if (f->x[k] < x && f->x[m] < x) return 0;
		if (f->x[k] > x && f->x[m] > x) return 0;

		t = (((f->y[k] - f->y[m]) / (f->x[k] - f->x[m])) *
		     (x - f->x[k])) + f->y[k];

		if (EQ(y, t)) return 0;
		if (t < y && f->y[i] < y) return 0;
		if (t > y && f->y[i] > y) return 0;

		return 1;
	}

	for (i = 0, k = 0; i < 3; i++) {
		if (f->x[i] < x && f->x[i + 1] < x) continue;
		if (f->x[i] > x && f->x[i + 1] > x) continue;

		t = (((f->y[i] - f->y[i + 1]) / (f->x[i] - f->x[i + 1])) *
		     (x - f->x[i])) + f->y[i];

		if (EQ(t, y))
			return 0;

		if (t > y)
			k++;
	}

	return (k & 1);
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
			f[n].x[3] = f[n].x[0];
			f[n].y[3] = f[n].y[0];
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
