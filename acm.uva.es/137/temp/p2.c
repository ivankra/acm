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

	return ((r < 0) ? (-r) : r) / 2.;
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

void hull(poly_t *r, double x[], double y[], int n)
{

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

printf("(%.2f,%.2f)-(%.2f,%.2f)  (%.2f,%.2f)-(%.2f,%.2f)  ",
  ax[0], ay[0], ax[1], ay[1], bx[0], by[0], bx[1], by[1]);

	t = c1 * d2 - c2 * d1;
printf("  t=%.3f\n",t);
	if (fabs(t) < EPS) return 0;

	*rx = (c3 * d2 - c2 * d3) / t;
	*ry = (c1 * d3 - c3 * d1) / t;

printf("R=(%.4f,%.4f)\n",*rx,*ry);
printf("%.5f=%.5f %.5f=%.5f\n",
  (*rx)*c1+(*ry)*c2,c3,
  (*rx)*d1+(*ry)*d2,d3);

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
