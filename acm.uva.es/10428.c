#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	int n;
	double a[8];
} poly_t;

int iszero(double x)
{
	return (-1e-12 < x && x < 1e-12);
}

double eval(poly_t *p, double x)
{
	double y;
	int i;

	for (y = 0, i = p->n; i >= 0; i--)
		y = y * x + p->a[i];

	return y;
}

void div1(poly_t *p, double x)
{
	double y, z;
	int i;

	for (y = 0, i = p->n--; i >= 0; i--, y = z) {
		z = y * x + p->a[i];
		p->a[i] = y;
	}

	if (p->n < 0) {
		p->n = 0;
		p->a[0] = 0;
	}
}

double rnd1()
{
	int m;

	m = (((rand() << 15) ^ rand()) & 0x7FFFFFFF);
	m %= 10000000;

	return ((double)m / 10000000.);
}

double rnd(double a, double b)
{
	return (a + ((b - a) * rnd1()));
}

int bis(poly_t *p, double r[])
{
	double a, b, c, d;

	c = eval(p, a = rnd(-25.00001, 25.00001));

	if (iszero(c)) {
		r[0] = a;
		return 1;
	}

	for (;;) {
		d = eval(p, b = rnd(-25.00001, 25.00001));

		if (iszero(d)) {
			r[0] = b;
			return 1;
		}

		if ((c * d) < 0)
			break;
	}

	d = c - d;

	if (a > b) {
		c = a;
		a = b;
		b = c;
		d = -d;
	}

	if (d > 0) {
		while ((b - a) > 1e-12) {
			d = eval(p, c = (a + b) / 2.);

			if (d > 0)
				a = c;
			else
				b = c;
		}

		r[0] = (a + b) / 2.;
		return 1;
	} else {
		while ((b - a) > 1e-12) {
			d = eval(p, c = (a + b) / 2.);

			if (d < 0)
				a = c;
			else
				b = c;
		}

		r[0] = (a + b) / 2.;
		return 1;
	}
}

int find(poly_t *p, double r[])
{
	int k;

	while (p->n > 0 && iszero(p->a[p->n]))
		p->n--;

	if (p->n == 0) {
		r[0] = 0;
		return 1;
	}

	if (p->n == 1) {
		r[0] = -(p->a[0] / p->a[1]);
		return 1;
	}

	if (p->n == 2) {
		double t;

		t = p->a[1] * p->a[1] - 4. * p->a[0] * p->a[2];
		t = (t < 0.) ? 0. : sqrt(t);

		r[0] = (-p->a[1] + t) / (2. * p->a[2]);
		r[1] = (-p->a[1] - t) / (2. * p->a[2]);
		return 2;
	}

	if ((k = bis(p, r)) > 0)
		return k;

	return 0;
}

int compare(const void *p, const void *q)
{
	return (((*(double *)p) > (*(double *)q)) ? 1 : -1);
}

int main()
{
	double r[16], x[16];
	poly_t p;
	int i, k, n, t;

	srand(53387);

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		for (i = p.n = n; i >= 0; i--)
			scanf("%lf", &p.a[i]);

		for (k = 0; k < n && (i = find(&p, x)) > 0;)
			while (i-- > 0)
				div1(&p, r[k++] = x[i]);

		qsort(r, k, sizeof(r[0]), &compare);

		printf("Equation %d:", t);
		for (i = 0; i < k; i++)
			printf(" %.4f", r[i]);
		printf("\n");
	}

	return 0;
}
