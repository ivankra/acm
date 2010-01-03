#include <stdio.h>
#include <math.h>

typedef struct {
	double la, lo;
} loc_t;

double pi;

double dist(double p1, double t1, double p2, double t2)
{
	double a = cos(p1) * cos(p2) * cos(t1 - t2) + sin(p1) * sin(p2);
	if (a < -1.) a = -1.;
	if (a > 1.) a = 1.;
	return acos(a) * 6371.01;
}

void get(loc_t *r)
{
	double a, b, c, t;
	char s[16];

	scanf("%lf %lf %lf %s", &a, &b, &c, s);

	t = (a + b / 60. + c / 3600.) * pi / 180;
	if (s[0] == 'S') t = -t;
	r->la = t;

	scanf("%lf %lf %lf %s", &a, &b, &c, s);

	t = (a + b / 60. + c / 3600.) * pi / 180;
	if (s[0] == 'W') t = -t;
	r->lo = t;
}

int main()
{
	int n;
	loc_t a, b;

	pi = 2. * acos(0.);

	for (scanf("%d", &n); n-- > 0;) {
		get(&a); get(&b);
		printf("%.2f\n", dist(a.la, a.lo, b.la, b.lo));
	}

	return 0;
}
