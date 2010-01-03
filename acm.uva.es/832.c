#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define EPS 1e-9

typedef struct {
	double x, dy;
} rec_t;

int cmp(const void *p, const void *q)
{
	return (((rec_t *)p)->x > ((rec_t *)q)->x) ? 1 : -1;
}

double sol()
{
	double num, den, x, y, dc;
	int i, n, m;
	rec_t *r;

	scanf("%d", &n);
	for (num = den = 0.; n-- > 0 && scanf("%lf %d", &dc, &m) == 2;) {
		r = (rec_t *)malloc((2 * m + 2) * sizeof(rec_t));
		for (i = 0; m-- > 0;) {
			scanf("%lf %lf %lf", &r[i].dy, &r[i].x, &r[i+1].x);
			r[i+1].dy = -r[i].dy;
			i += 2;
		}

		qsort(r, m = i, sizeof(rec_t), &cmp);

		for (i = 0, x = -1, y = 0.; i < m;) {
			den += (r[i].x - x) * y;
			if (y >= dc) num += (r[i].x - x) * (y - dc);
			for (x = r[i].x; i < m && fabs(r[i].x - x) < EPS;)
				y += r[i++].dy;
		}

		assert(fabs(y) < EPS);

		free(r);
	}

	assert(fabs(den) > EPS);
	return (num * 100. / den);
}

int main()
{
	int t;
	for (scanf("%d", &t); t-- > 0;)
		printf("%.2f%%\n%s", sol() - 0.005, t ? "\n" : "");
	return 0;
}
