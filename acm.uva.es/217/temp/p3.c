#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define EPS 1e-9

typedef struct { double x, y; } pair_t;

struct {
	char name[256];
	pair_t loc;
} beacon[32];

int nbeacons;
double pi;

int sol1(pair_t *r, double d, double a[2], pair_t p[2])
{
	double t, t0, t1, x0, x1;

printf("\n");
printf("d=%.5f, (x=%.5f,y=%.5f,a=%.5f), (x=%.5f,y=%.5f,a=%.5f)\n",
  d, p[0].x, p[0].y, a[0], p[1].x, p[1].y, a[1]);

	while (a[0] < 0) a[0] += pi;
	while (a[0] > pi) a[0] -= pi;

	while (a[1] < 0) a[1] += pi;
	while (a[1] > pi) a[1] -= pi;

	if (fabs(a[0] - pi) < EPS) a[0] = 0;
	if (fabs(a[1] - pi) < EPS) a[1] = 0;

	t = fabs(a[0] - a[1]);
	if (fabs(t) < EPS || fabs(t - pi) < EPS)
		return 0;

	if (fabs(a[0]) < EPS || fabs(a[1]) < EPS) {
printf("sol1: n/a feature\n");
exit(1);
		return 0;
	}

printf("a0=%.5f a1=%.5f\n",a[0],a[1]);

	t0 = 1. / tan(a[0]);
	t1 = 1. / tan(a[1]);

	x0 = p[0].x - p[0].y * t0;
	x1 = p[1].x - p[1].y * t1;

printf("t0=%.5f t1=%.5f x0=%.5f x1=%.5f\n",t0,t1,x0,x1);

	r->y = (d - x1 + x0) / (t1 - t0);
	r->x = x1 + r->y * t1;

printf("R=(%.5f, %.5f)\n", r->x, r->y);

	return 1;
}

pair_t rot(pair_t p, double a)
{
	pair_t q;
	q.x = p.x * cos(a) - p.y * sin(a);
	q.y = p.x * sin(a) + p.y * cos(a);
	return q;
}

int sol(pair_t *r, double c, double d, double a[2], pair_t p[2])
{
	double t = -c;
	pair_t q[2], z;

	a[0] += t;
	a[1] += t;

	q[0] = rot(p[0], t);
	q[1] = rot(p[1], t);

	if (sol1(&z, d, a, q) == 0)
		return 0;

	*r = rot(z, -t);

{ pair_t p = { 6, 5 };
  p = rot(p, t);
  printf("need: (%.5f, %.5f)\n", p.x, p.y);
}
	return 1;
}

pair_t getloc()
{
	static char s[256];
	int i;

	scanf(" %s", s);

	for (i = 0; i < nbeacons; i++)
		if (strcmp(beacon[i].name, s) == 0) break;

	assert(i < nbeacons);
	return beacon[i].loc;
}

int main()
{
	pair_t p[2], r;
	double course, speed, tm[2], a[2], d;
	int i, m, t;

	pi = 2. * acos(0.);

	for (t = 1; scanf("%d", &nbeacons) == 1;) {
		for (i = 0; i < nbeacons; i++)
			scanf(" %s %lf %lf",
			      beacon[i].name,
			      &beacon[i].loc.x, &beacon[i].loc.y);

		for (scanf("%d", &m); m-- > 0; t++) {
			scanf("%lf %lf %lf", &course, &speed, &tm[0]);
			p[0] = getloc();
			scanf("%lf %lf", &a[0], &tm[1]);
			p[1] = getloc();
			scanf("%lf", &a[1]);

			a[0] = (90. - course - a[0]) * pi / 180.;
			a[1] = (90. - course - a[1]) * pi / 180.;
			course = (90. - course) * pi / 180.;

			d = fabs(tm[1] - tm[0]) * speed;

			printf("Scenario %d: ", t);
			if (sol(&r, course, d, a, p))
				printf("Position is (%.2f, %.2f)\n", r.x, r.y);
			else
				printf("Position cannot be determined\n");
		}
	}

	return 0;
}
