#include <stdio.h>

#define MAXN 1024

typedef struct {
	int x[MAXN], y[MAXN], n;
} ipoly_t;

typedef struct {
	double x[MAXN], y[MAXN];
	int n;
} poly_t;

int iread(ipoly_t *p)
{
	int i;

	if (scanf("%d", &p->n) != 1 || p->n < 3)
		return 0;

	for (i = 0; i < p->n; i++)
		scanf("%d %d", &p->x[i], &p->y[i]);

	p->x[p->n] = p->x[0];
	p->y[p->n] = p->y[0];
	return 1;
}

int iarea2(ipoly_t *p)
{
	int r, i;

	for (r = 0, i = 0; i < p->n; i++) {
		r += (p->x[i + 1] - p->x[0]) * (p->y[i] - p->y[0]);
		r -= (p->x[i] - p->x[0]) * (p->y[i + 1] - p->y[0]);
	}

	return (r < 0) ? (-r) : r;
}

int area(poly_t *p)
{
	int i;
	double r;

	for (r = 0, i = 0; i < p->n; i++) {
		r += (p->x[i + 1] - p->x[0]) * (p->y[i] - p->y[0]);
		r -= (p->x[i] - p->x[0]) * (p->y[i + 1] - p->y[0]);
	}

	return ((r < 0) ? (-r) : r) / 2.;
}

int main()
{
	static ipoly_t p, q;

	while (iread(&p) && iread(&q)) {
		printf("areas: %d/2 %d/2\n", iarea2(&p), iarea2(&q));

	}

	printf("\n");

	return 0;
}
