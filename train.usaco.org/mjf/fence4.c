/*
ID: mjf28791
PROG: fence4
LANG: C
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-9

typedef long long llong;

typedef struct {
	llong x[2], y[2], a, b, c;
} seg_t;

typedef struct {
	double x;
	int s;
} rec_t;

typedef struct {
	int a, b;
} out_t;

llong fx[1024], fy[1024];
int fv[1024], fn;

double fv1[1024], fv2[1024];

int eq(double a, double b)
{
	return (fabs(a - b) < EPS);
}

int eqz(double x)
{
	return (fabs(x) < EPS);
}

int lbetween(llong a, llong x, llong b)
{
	return (a < x && x < b);
}

int sbetween(double a, double x, double b)
{
	return (((a - EPS) < x && x < (b + EPS)) ||
		((b - EPS) < x && x < (a + EPS)));
}

seg_t seg(llong x0, llong y0, llong x1, llong y1)
{
	seg_t s;

	s.x[0] = x0;
	s.y[0] = y0;
	s.x[1] = x1;
	s.y[1] = y1;

	s.a = y1 - y0;
	s.b = x0 - x1;
	s.c = x0 * s.a + y0 * s.b;

	return s;
}

seg_t seg2(llong x[], llong y[])
{
	return seg(x[0], y[0], x[1], y[1]);
}

int inter1(seg_t s, seg_t t)
{
	llong d;
	double xs, ys;

	d = s.a * t.b - s.b * t.a;

	if (d == 0) {
		if (s.b * t.c != s.c * t.b || s.a * t.c != s.c * t.a)
			return 0;

		if (lbetween(s.x[0], t.x[0], s.x[1]) && lbetween(s.y[0], t.y[0], s.y[1]))
			return -1;

		if (lbetween(s.x[0], t.x[1], s.x[1]) && lbetween(s.y[0], t.y[1], s.y[1]))
			return -1;

		if (lbetween(t.x[0], s.x[0], t.x[1]) && lbetween(t.y[0], s.y[0], t.y[1]))
			return -1;

		if (lbetween(t.x[0], s.x[1], t.x[1]) && lbetween(t.y[0], s.y[1], t.y[1]))
			return -1;

		return 0;
	}

	xs = (s.c * t.b - s.b * t.c) / (double)d;
	ys = (s.a * t.c - s.c * t.a) / (double)d;

	if (xs < (s.x[0] - EPS) && xs < (s.x[1] - EPS)) return 0;
	if (xs > (s.x[0] + EPS) && xs > (s.x[1] + EPS)) return 0;
	if (xs < (t.x[0] - EPS) && xs < (t.x[1] - EPS)) return 0;
	if (xs > (t.x[0] + EPS) && xs > (t.x[1] + EPS)) return 0;
	if (ys < (s.y[0] - EPS) && ys < (s.y[1] - EPS)) return 0;
	if (ys > (s.y[0] + EPS) && ys > (s.y[1] + EPS)) return 0;
	if (ys < (t.y[0] - EPS) && ys < (t.y[1] - EPS)) return 0;
	if (ys > (t.y[0] + EPS) && ys > (t.y[1] + EPS)) return 0;

	if (eq(xs, s.x[0]) && eq(ys, s.y[0])) return 0;
	if (eq(xs, s.x[1]) && eq(ys, s.y[1])) return 0;
	if (eq(xs, t.x[0]) && eq(ys, t.y[0])) return 0;
	if (eq(xs, t.x[1]) && eq(ys, t.y[1])) return 0;

	return 1;
}

int check()
{
	int i, j;
	llong a;

	if (fn < 3)
		return 1;

	for (i = 0; i < fn; i++)
		for (j = 0; j < fn; j++)
			if (i != j && fx[i] == fx[j] && fy[i] == fy[j])
				return 1;

	for (i = 0; i < fn; i++)
		for (j = 0; j < fn; j++)
			if (i != j &&
			    inter1(seg2(fx+i, fy+i), seg2(fx+j, fy+j)))
				return 1;

	for (a = 0, i = 0; i < fn; i++) {
		a += (fx[i] - fx[0]) * (fy[i + 1] - fy[0]);
		a -= (fx[i + 1] - fx[0]) * (fy[i] - fy[0]);
	}

	if (a <= 0)
		return 1;

	return 0;
}

int cmp(const void *p, const void *q)
{
	rec_t *a = (rec_t *)p, *b = (rec_t *)q;
	return (a->x > b->x) ? 1 : -1;
}

double gx[1024], gy[1024];

int edge(double x1, double x2)
{
	int i;

	for (i = 0; i < fn; i++) {
		if (!eqz(gy[i]) || !eqz(gy[i+1])) continue;

		if (sbetween(gx[i], x1, gx[i+1]) && sbetween(gx[i], x2, gx[i+1]))
			return 1;
	}

	return 0;
}

void trace(double x0, double y0, double x1, double y1)
{
	static rec_t a[2048];
	double u, v, t;
	int i, m;

	if (eq(x0, x1) && eq(y0, y1)) return;

	x1 -= x0;
	y1 -= y0;

	t = sqrt(x1 * x1 + y1 * y1);
	u = x1 / t;
	v = y1 / t;

	for (i = 0; i < fn; i++) {
		gx[fn + i] = gx[i] = (fx[i] - x0) * u + (fy[i] - y0) * v;
		gy[fn + i] = gy[i] = (x0 - fx[i]) * v + (fy[i] - y0) * u;
	}

	for (m = 0, i = 0; i < fn; i++) {
		if (eqz(gy[i]) && eqz(gy[i+1]))
			continue;

		if (eqz(gy[i])) {
			if (gy[i + 1] > 0 && gx[i] > -EPS)
				a[m].x = gx[i], a[m++].s = -1;
			continue;
		}

		if (eqz(gy[i + 1])) {
			if (gy[i] > 0 && gx[i+1] > -EPS)
				a[m].x = gx[i+1], a[m++].s = -1;
			continue;
		}

		if (gy[i] * gy[i + 1] > 0)
			continue;

		t = gx[i] - gy[i] * (gx[i] - gx[i+1]) / (gy[i] - gy[i+1]);
		if (t > -EPS) {
			a[m].x = t;
			a[m].s = i;
			m++;
		}
	}

	qsort(a, m, sizeof(a[0]), &cmp);

	for (i = 0; i < m;) {
		if (eq(a[i].x, a[i+1].x))
			i += 2;
		else if ((i + 1) < m && edge(a[i].x, a[i+1].x))
			i += 2;
		else
			break;
	}

	if (i >= m || a[i].s < 0)
		return;

	m = a[i].s;
	t = (a[i].x - gx[m]) * (a[i].x - gx[m]) + gy[m] * gy[m];

	if (fv[m] == 0) {
		fv[m] = 1;
		fv1[m] = fv2[m] = t;
	} else {
		if (t < fv1[m]) fv1[m] = t;
		if (t > fv2[m]) fv2[m] = t;
	}
}

int cmp2(const void *p, const void *q)
{
	out_t *x = (out_t *)p, *y = (out_t *)q;
	return (x->b != y->b) ? (x->b - y->b) : (x->a - y->a);
}

int main()
{
	static out_t z[1024];
	llong x0, y0;
	int i, k, t;

	freopen("fence4.in", "r", stdin);
	freopen("fence4.out", "w", stdout);

	scanf("%d %lld %lld", &fn, &x0, &y0);
	for (i = 0; i < fn; i++) {
		scanf("%lld %lld", &fx[i], &fy[i]);
		fx[fn + i] = fx[i];
		fy[fn + i] = fy[i];
	}

	if (check()) {
		printf("NOFENCE\n");
		return 0;
	}

	memset(fv, 0, sizeof(fv));

	for (i = 0; i < fn; i++) {
		if (x0 != fx[i] || y0 != fy[i]) trace(x0, y0, fx[i], fy[i]);
		trace(x0, y0, fx[i] + 0.1, fy[i] - 0.1);
		trace(x0, y0, fx[i] - 0.1, fy[i] + 0.1);
	}

	for (i = 0; i < fn; i++) {
		trace(x0, y0, (fx[i] + fx[i+1]) / 2., (fy[i] + fy[i+1]) / 2.);
		trace(x0, y0, (2 * fx[i] + fx[i+1]) / 3., (2 * fy[i] + fy[i+1]) / 3.);
		trace(x0, y0, (fx[i] + 2 * fx[i+1]) / 3., (fy[i] + 2 * fy[i+1]) / 3.);
	}

	for (k = 0, i = 0; i < fn; i++) {
		if (fv[i] == 0 || eq(fv1[i], fv2[i])) continue;

		z[k].a = i;
		z[k].b = (i + 1) % fn;
		if (z[k].a > z[k].b)
			t = z[k].a, z[k].a = z[k].b, z[k].b = t;
		k++;
	}

	qsort(z, k, sizeof(z[0]), &cmp2);

	printf("%d\n", k);
	for (i = 0; i < k; i++)
		printf("%lld %lld %lld %lld\n",
			fx[z[i].a], fy[z[i].a], fx[z[i].b], fy[z[i].b]);

	return 0;
}
