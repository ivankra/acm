#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define EPS 1e-9

typedef struct { double x, y; } pair_t;
double pi;

int sol1(pair_t *r, double d, double a[], pair_t p[])
{

	return 0;
}

pair_t rot(pair_t p, double a)
{
	pair_t q;
	q.x = p.x * cos(a) - p.y * sin(a);
	q.y = p.x * sin(a) + p.y * cos(a);
	return q;
}

int sol(pair_t *r, double c, double d, double a[], pair_t p[])
{
	pair_t q[2];

	q[0] = rot(p[0], -c);
	q[1] = rot(p[1], -c);

	a[0] -= c;
	a[1] -= c;

	if (sol1(r, d, a, q) == 0)
		return 0;

	*r = rot(*r, c);
	return 1;
}

int main()
{
	static char bs[32][256], s1[256], s2[256];
	static pair_t bp[32], b[2], r;
	double c, s, t[2], a[2];
	int i, j, n, m, z;

	pi = 2. * acos(0.);

	for (z = 1; scanf("%d", &n) == 1;) {
		for (i = 0; i < n; i++)
			scanf(" %s %lf %lf", bs[i], &bp[i].x, &bp[i].y);

		for (scanf("%d", &m); m-- > 0; z++) {
			scanf("%lf %lf %lf %s %lf %lf %s %lf",
			      &c, &s, &t[0], s1, &a[0], &t[1], s2, &a[1]);

			for (i = 0; i < n; i++)
				if (strcmp(bs[i], s1) == 0) break;

			for (j = 0; j < n; j++)
				if (strcmp(bs[j], s2) == 0) break;

			assert(i < n && j < n);

			a[0] = (90. - c - a[0]) * pi / 180.;
			a[1] = (90. - c - a[1]) * pi / 180.;
			c = (90. - c) * pi / 180.;

			b[0] = bp[i];
			b[1] = bp[j];

			printf("Scenario %d: ", z);
			if (sol(&r, c, fabs(t[1] - t[0]) * s, a, b))
				printf("Position is (%.2f, %.2f)\n", r.x, r.y);
			else
				printf("Position cannot be determined\n");
		}
	}

	return 0;
}
