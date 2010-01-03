#include <stdio.h>
#include <math.h>
#define EPS 1e-8

typedef struct { double x,y; } vec;
vec P[1024];
double R;
int n;

double sq(double x) { return x*x; }
double dot(vec a, vec b) { return a.x*b.x+a.y*b.y; }

int chk2(double x, double y)
{
	for (int i = 0; i < n; i++)
		if (sq(P[i].x-x)+sq(P[i].y-y) > R*R+EPS) return 0;
	return 1;
}

int chk(vec p, vec q)
{
	vec c = {(p.x+q.x)/2., (p.y+q.y)/2.}, d = { p.y - q.y, q.x - p.x };
	double t = sqrt(dot(d,d));

	if (fabs(t) < EPS) return 0;
	d.x /= t; d.y /= t;

	t = R*R - 0.25*(sq(p.x-q.x)+sq(p.y-q.y));
	if (fabs(t) < EPS) t = 0.;
	else if (t < 0.) return 0;
	t = sqrt(t);

	return (chk2(c.x+t*d.x,c.y+t*d.y) || chk2(c.x-t*d.x,c.y-t*d.y));
}

int solve()
{
	if (n <= 1) return 1;

	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (chk(P[i],P[j])) return 1;

	return 0;
}

int main()
{
	while (scanf("%d", &n) == 1 && n > 0) {
		for (int i = 0; i < n; i++) scanf("%lf %lf", &P[i].x, &P[i].y);
		scanf("%lf", &R);
		printf(solve() ? "The polygon can be packed in the circle.\n" :
				 "There is no way of packing that polygon.\n");
	}
	return 0;
}
