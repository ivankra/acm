#include <cstdio>
#include <cmath>
#include <algorithm>
#define EPS 1e-9
using namespace std;

struct Point {
	double x, y;
	Point(double x, double y) : x(x), y(y) {}
};

Point operator +(Point a, Point b) { return Point(a.x+b.x, a.y+b.y); }
Point operator -(Point a, Point b) { return Point(a.x-b.x, a.y-b.y); }
double operator *(Point a, Point b) { return a.x*b.x+a.y*b.y; }
double cross(Point a, Point b) { return a.x*b.y-a.y*b.x; }
double len(Point a) { return sqrt(a*a); }
Point ren(Point p, double n) { n /= len(p); return Point(p.x*n, p.y*n); }
double ang(Point a, Point b) { return acos(a * b / (len(a) * len(b))); }
double sq(double x) { return x*x; }
Point rot(Point p, double t) {
	return Point(p.x*cos(t)-p.y*sin(t), p.x*sin(t)+p.y*cos(t));
}

double PI=2*acos(0.), l, w, R;

double solve()
{
	if (w > l) swap(w, l);

	if (w < EPS) return PI*R*R;

	if (R < l+w+EPS)
		return PI*(R*R*0.75 + 0.25*(sq((R-w) >? 0) + sq((R-l) >? 0)));

	double r1 = R - w, r2 = R - l;
	Point A(w,0), B(0,l);

	double d = len(A-B), t = acos((r1*r1 + d*d - r2*r2) / (2 * r1 * d));

	Point S1 = A + ren(rot(B-A, t), r1), S2 = A + ren(rot(B-A, -t), r1);
	Point S = (cross(S1-A,B-A) > -EPS) ? S1 : S2;

//	assert(S.x > w-EPS && S.y > l-EPS);

	double z = PI*R*R*0.75;
	z += 0.5 * r1 * r1 * ang(S-A, Point(R,0)-A);
	z += 0.5 * r2 * r2 * ang(S-B, Point(0,R)-B);
	z += fabs(cross(S1-A,B-A)) / 2 - l * w / 2;

	return z;
}

int main()
{
	while (scanf("%lf %lf %lf", &l, &w, &R) == 3)
		printf("%.10lf\n", solve());
	return 0;
}
