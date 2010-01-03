#include <stdio.h>
#include <math.h>
#include <algorithm>
#define EPS 1e-9
using namespace std;

struct obj {
	int x1, y1, x2, y2, f;
	int a, b, c;
};

int in(double x, double y, obj s)
{
	if (s.f == 0) return 1;
	if (x < s.x1-EPS && x < s.x2-EPS) return 0;
	if (x > s.x1+EPS && x > s.x2+EPS) return 0;
	if (y < s.y1-EPS && y < s.y2-EPS) return 0;
	if (y > s.y1+EPS && y > s.y2+EPS) return 0;
	return 1;
}

double ldist(obj l, int x, int y)
{
	double r;

	if (l.f == 0) return fabs(l.a*x+l.b*y-l.c)/sqrt(l.a*l.a+l.b*l.b);

	r = sqrt((x-l.x1)*(x-l.x1)+(y-l.y1)*(y-l.y1));
	r = min(r, sqrt((x-l.x2)*(x-l.x2)+(y-l.y2)*(y-l.y2)));

	double t = l.x1*(l.x1-l.x2)+l.y1*(l.y1-l.y2)+y*(l.y2-l.y1)+x*(l.x2-l.x1);
	t /= (l.x2-l.x1)*(l.x2-l.x1) + (l.y2-l.y1)*(l.y2-l.y1);

	if (t < -EPS || t > 1+EPS) return r;

	double xi = l.x1 + t * (l.x2 - l.x1), yi = l.y1 + t * (l.y2 - l.y1);

	r = min(r, sqrt((x-xi)*(x-xi)+(y-yi)*(y-yi)));

	return r;
}

double solve(obj a, obj b)
{
	a.a = a.y1 - a.y2;
	a.b = a.x2 - a.x1;
	a.c = a.a * a.x1 + a.b * a.y1;

	b.a = b.y1 - b.y2;
	b.b = b.x2 - b.x1;
	b.c = b.a * b.x1 + b.b * b.y1;

	int d = a.a * b.b - a.b * b.a;
	if (d != 0) {
		double x0 = (a.c * b.b - a.b * b.c) / (double)d;
		double y0 = (a.a * b.c - a.c * b.a) / (double)d;
		if (in(x0,y0,a) && in(x0,y0,b)) return 0.;
	}

	double r = ldist(a, b.x1, b.y1);
	r = min(r, ldist(a, b.x2, b.y2));
	r = min(r, ldist(b, a.x1, a.y1));
	r = min(r, ldist(b, a.x2, a.y2));
	return r;
}

int main()
{
	int i;
	char s[16];
	obj a, b;

	for (;;) {
		i = scanf("%d %d %d %d %s", &a.x1, &a.y1, &a.x2, &a.y2, s);
		if (i != 5 || s[0] == 'E') break;
		a.f = (s[1] == 'S') ? 1 : 0;

		i = scanf("%d %d %d %d %s", &b.x1, &b.y1, &b.x2, &b.y2, s);
		if (i != 5 || s[0] == 'E') break;
		b.f = (s[1] == 'S') ? 1 : 0;

		printf("%.5f\n", solve(a,b)+1e-12);
	}

	return 0;
}
