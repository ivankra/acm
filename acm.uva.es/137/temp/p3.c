#include <stdio.h>
#include <math.h>

#define MAXN	1024
#define EPS	1e-9

typedef struct {
	double x[MAXN], y[MAXN];
	int n;
} poly_t;

int pread(poly_t *p)
{
	int i;

	if (scanf("%d", &p->n) != 1 || p->n < 3)
		return 0;

	for (i = 0; i < p->n; i++)
		scanf("%lf %lf", &p->x[i], &p->y[i]);

	p->x[p->n] = p->x[0];
	p->y[p->n] = p->y[0];
	return 1;
}

double area(poly_t *p)
{
	int i;
	double r;

	for (r = 0, i = 0; i < p->n; i++) {
		r += (p->x[i + 1] - p->x[0]) * (p->y[i] - p->y[0]);
		r -= (p->x[i] - p->x[0]) * (p->y[i + 1] - p->y[0]);
	}

	return (fabs(r) / 2.);
}

int in_poly(poly_t *p, double x, double y)
{
	int i;
	double t;

	for (i = 0; i < p->n; i++) {
		t = (p->x[i + 1] - x) * (p->y[i] - y);
		t -= (p->x[i] - x) * (p->y[i + 1] - y);
		if (t < -EPS) return 0;
	}

	return 1;
}

double sq(double x)
{
	return x * x;
}

int hull(int h[], double x[], double y[], int n)
{
	int i, j, k, p;
	double t;

	if (n < 3)
		return 0;

	for (p = 0, i = 1; i < n; i++)
		if ((x[i] < (x[p] - EPS)) ||
 		    (fabs(x[i] - x[p]) < EPS && y[i] < y[p]))
			p = i;

	for (h[0] = p, k = 1;;) {
		for (j = -1, i = 0; i < n; i++) {
			if (fabs(x[i] - x[p]) < EPS && fabs(y[i] - y[p]) < EPS)
				continue;

			if (j < 0) {
				j = i;
				continue;
			}

			t = (x[j] - x[p]) * (y[i] - y[p]);
			t -= (x[i] - x[p]) * (y[j] - y[p]);

			if (t < -EPS)
				continue;

			if (fabs(t) < EPS) {
				t = sq(x[i] - x[p]) + sq(y[i] - y[p]);
				t -= sq(x[j] - x[p]) + sq(y[j] - y[p]);
				if (t < 0) continue;
			}

			j = i;
		}

		if (j < 0 || (fabs(x[j] - x[h[0]]) < EPS && fabs(y[j] - y[h[0]]) < EPS))
			break;

		h[k++] = j;
		p = j;
	}

	h[k] = h[0];
	return k;
}

int isect(double ax[], double ay[], double bx[], double by[], double *rx, double *ry)
{
	double c1, c2, c3, d1, d2, d3, t;

	c1 = ay[1] - ay[0];
	c2 = ax[0] - ax[1];
	c3 = ax[0] * c1 + ay[0] * c2;

	d1 = by[1] - by[0];
	d2 = bx[0] - bx[1];
	d3 = bx[0] * d1 + by[0] * d2;

	t = c1 * d2 - c2 * d1;
	if (fabs(t) < EPS) return 0;

	*rx = (c3 * d2 - c2 * d3) / t;
	*ry = (c1 * d3 - c3 * d1) / t;

	if (fabs((*rx) - ax[0]) < EPS && fabs((*ry) - ay[0]) < EPS) return 0;
	if (fabs((*rx) - ax[1]) < EPS && fabs((*ry) - ay[1]) < EPS) return 0;
	if (fabs((*rx) - bx[0]) < EPS && fabs((*ry) - by[0]) < EPS) return 0;
	if (fabs((*rx) - bx[1]) < EPS && fabs((*ry) - by[1]) < EPS) return 0;

	if (*rx < (ax[0] - EPS) && *rx < (ax[1] - EPS)) return 0;
	if (*rx > (ax[0] + EPS) && *rx > (ax[1] + EPS)) return 0;
	if (*ry < (ay[0] - EPS) && *ry < (ay[1] - EPS)) return 0;
	if (*ry > (ay[0] + EPS) && *ry > (ay[1] + EPS)) return 0;

	if (*rx < (bx[0] - EPS) && *rx < (bx[1] - EPS)) return 0;
	if (*rx > (bx[0] + EPS) && *rx > (bx[1] + EPS)) return 0;
	if (*ry < (by[0] - EPS) && *ry < (by[1] - EPS)) return 0;
	if (*ry > (by[0] + EPS) && *ry > (by[1] + EPS)) return 0;

	return 1;
}

double solve(poly_t *p, poly_t *q)
{
	static double x[65536], y[65536];
	static int h[65536];
	static poly_t r;
	int i, j, n;

	n = 0;

	for (i = 0; i < p->n; i++)
		if (in_poly(q, p->x[i], p->y[i]))
			x[n] = p->x[i], y[n] = p->y[i], n++;

	for (i = 0; i < q->n; i++)
		if (in_poly(p, q->x[i], q->y[i]))
			x[n] = q->x[i], y[n] = q->y[i], n++;

	for (i = 0; i < p->n; i++)
		for (j = 0; j < p->n; j++)
			n += isect(p->x + i, p->y + i, q->x + j, q->y + j, &x[n], &y[n]);

printf("n=%d: ", n);
for (i=0;i<n;i++)
{printf("(%.2f,%.2f) ",x[i],y[i]);}
printf("\n");

	r.n = hull(h, x, y, n);

	for (i = 0; i <= r.n; i++) {
		r.x[i] = x[h[i]];
		r.y[i] = y[h[i]];
	}

printf("Hull: n=%d,  ", n);
for (i=0;i<n;i++)
{printf("(%.2f,%.2f) ",x[h[i]],y[h[i]]);}
printf("\n");

	printf("hull's area=%.3f\n", area(&r));

	printf("P=%.3f Q=%.3f R=%.3f\n", area(p), area(q), area(&r));

	printf("result=%.5f\n", area(p) + area(q) - 2. * area(&r));

	return 0.;
}

int main()
{
	static poly_t p, q;

	while (pread(&p) && pread(&q)) {
		solve(&p, &q);
	}

	printf("\n");
	return 0;
}
