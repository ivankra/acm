#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#define EPS 1e-9

typedef struct { double a[16]; int n; } poly;
typedef struct { double x, y; } pt;

double eval(poly P, double x)
{
	double r;
	int i;
	for (r = 0., i = P.n; i >= 0; i--)
		r = r * x + P.a[i];
	return r;
}

poly deriv(poly P)
{
	poly Q;
	int i;

	if (P.n < 1) { Q.a[0] = 0.; Q.n = 0; return Q; }

	Q.n = P.n - 1;
	for (i = 1; i <= P.n; i++)
		Q.a[i-1] = i * P.a[i];
	return Q;
}

poly pdiv(poly P, double x)
{
	poly Q;
	double r;
	int i;

	Q.n = P.n - 1;
	for (r = 0., i = P.n; i >= 0; i--) {
		Q.a[i] = r;
		r = r * x + P.a[i];
	}

	return Q;
}

int sgn(double x)
{
	if (fabs(x) < EPS) return 0;
	return (x > 0.) ? 1 : -1;
}

int cmp_d(const void *p, const void *q)
{
	return (*(double *)p > *(double *)q) ? 1 : -1;
}

int bisec(double *r, poly P, double a, double b)
{
	double c;
	int u, v, t;

	if (a > b) { c = a; a = b; b = c; }

	if ((u = sgn(eval(P, a))) == 0) { *r = a; return 1; }
	if ((v = sgn(eval(P, b))) == 0) { *r = b; return 1; }

	if (u == v) return 0;

	while ((b - a) > 1e-13) {
		t = sgn(eval(P, c = (a + b) / 2.));
		if (t == 0) { *r = c; return 1; }
		if (u == t) a = c; else b = c;
	}

	return 0;
}

int roots(poly P, double r[])
{
	int i, qn;
	poly Q;
	double qr[16];

	while (P.n > 0 && fabs(P.a[P.n]) < EPS) P.n--;
	for (i = 0; i <= P.n; i++) P.a[i] /= P.a[P.n];

	if (P.n < 1) return 0;

	if (P.n == 1) {
		r[0] = -P.a[0] / P.a[1];
		return 1;
	}

	if (P.n == 2) {
		double d = P.a[1] * P.a[1] - 4. * P.a[0] * P.a[2];

		if (fabs(d) < EPS) { r[0] = -P.a[1] / (2. * P.a[2]); return 1; }
		if (d < 0) return 0;

		d = sqrt(d);
		r[0] = (-P.a[1] - d) / (2. * P.a[2]);
		r[1] = (-P.a[1] + d) / (2. * P.a[2]);
		return 2;
	}

/*printf("roots: P(x)=");for(i=P.n;i>=0;i--)printf(" + %.4fx^%d",P.a[i],i);printf("\n");*/

	Q = deriv(P);
	qn = roots(Q, qr+1);
	qsort(qr+1, qn, sizeof(qr[0]), &cmp_d);
	qr[0] = -1e30;
	qr[qn+1] = 1e30;

	for (i = 0; i <= qn; i++)
		if (bisec(&r[0], P, qr[i], qr[i+1])) {
/*printf("found root: %.5f\n", r[0]);*/
			Q = pdiv(P, r[0]);
			return 1+roots(Q,r+1);
		}

	return 0;
}

int cmp_pt(const void *pp, const void *qq)
{
	pt *p = (pt *)pp, *q = (pt *)qq;
	if (fabs(p->x - q->x) < 1e-5) return (p->y > q->y) ? 1 : -1;
	return (p->x > q->x) ? 1 : -1;
}

int uniq(double r[], int n)
{
	int i, j, k;

	for (i = k = 0; i < n; i++) {
		for (j = 0; j < k; j++)
			if (fabs(r[i] - r[j]) < 1e-9) break;
		if (j < k) continue;
		r[k++] = r[i];
	}

	return k;
}

void solve(double a, double b, double p, double q, int an, int bn, int pn, int qn)
{
	poly P={{-b*q,2*a*p-2*a*a+2*b*b,0,2*a*p+2*a*a-2*b*b,b*q},4};
	double u[16], t; pt r[16];
	int i, j, n;

	n = roots(P, u);
	n = uniq(u, n);

	for (i = 0; i < n; i++) {
		t = 2 * atan(u[i]);
		r[i].x = a * cos(t);
		r[i].y = b * sin(t);
	}

	if (pn == 0) {
		r[n].x = 0; r[n++].y = b;
		r[n].x = 0; r[n++].y = -b;
	}

	if (qn == 0) {
		r[n].x = -a; r[n++].y = 0;
		r[n].x = a; r[n++].y = 0;
	}

	qsort(r, n, sizeof(r[0]), &cmp_pt);

	for (i = 0; i < n; i++) {
		for (j = 0; j < i; j++)
			if (fabs(r[i].x-r[j].x) < 1e-5 && fabs(r[i].y-r[j].y)<1e-5) break;
		if (j < i) continue;
		printf("%.5f %.5f\n", r[i].x, r[i].y);
	}
}

int main()
{
	int a, b, p, q, t;

	srand(53387);

	for (t = 1; scanf("%d %d %d %d", &a, &b, &p, &q) == 4 && a >= 0; t++) {
		assert(1<=a&&a<=300 && 1<=b&&b<=300);
		assert(-300<=p&&p<=300 && -300<=q&&q<=300);
		printf("Case %d:\n", t);
		solve(a,b,p,q,a,b,p,q);
	}

	return 0;
}
