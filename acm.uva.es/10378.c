#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	double x, y;
} pair_t;

int cmp(const void *p, const void *q)
{
	pair_t *a = (pair_t *)p, *b = (pair_t *)q;

	if (fabs(a->x - b->x) > 1e-6)
		return (a->x > b->x) ? -1 : 1;
	else
		return (a->y > b->y) ? -1 : 1;
}

double cvt(double x)
{
	if (x > 0.)
		return x;
	else if (x > -0.0005)
		return 0.;
	else
		return x;
}

int main()
{
	static pair_t c[1024];
	double r, z, a, b, t, p;
	int i, n, cs;

	p = 4. * acos(0.);

	for (cs = 1; scanf("%lf %lf i %d", &a, &b, &n) == 3; cs++) {
		printf("Case %d:\n", cs);

		r = pow(a * a + b * b, 1. / (2. * n));
		z = atan2(b, a);

		for (i = 0; i < n; i++) {
			t = (z + p * i) / (double)n;
			c[i].x = cvt(r * cos(t));
			c[i].y = cvt(r * sin(t));
		}

		qsort(c, n, sizeof(c[0]), &cmp);

		for (i = 0; i < n; i++)
			printf("%.3f%+.3fi\n", cvt(c[i].x), cvt(c[i].y));
		printf("\n");
	}

	return 0;
}
