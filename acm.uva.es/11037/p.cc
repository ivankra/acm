#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

#define EPS 1e-9

double dist(double x, double y) { return sqrt(x*x+y*y); }
double sq(double x) { return x*x; }

struct Point {
	double x, y;
	Point(double X=0, double Y=0) : x(X), y(Y) {}
};

double dot(const Point &p, const Point &q) { return p.x*q.x+p.y*q.y; }

struct Line {
	// ax + by + c = 0
	double a, b, c;
	Line(double A, double B, double C) : a(A), b(B), c(C) {}
};

vector<Point> isect(Line l, Line m) {
	double det = l.a * m.b - m.a * l.b;
	if (fabs(det) < EPS) return vector<Point>();

	vector<Point> v;
	v.push_back(Point((l.b*m.c-l.c*m.b)/det, (l.c*m.a-l.a*m.c)/det));
	return v;
}

struct Quad {
	// a(x^2 + y^2) + bx + cy + d = 0
	double a, b, c, d;
	double eval(double x, double y) {
		return a*(x*x+y*y)+b*x+c*y+d;
	}
	void circ(double x1, double y1, double r1, double x2, double y2, double r2) {
		double r = sq(r1 / r2);
		a = 1 - r;
		b = 2 * r * x2 - 2 * x1;
		c = 2 * r * y2 - 2 * y1;
		d = sq(x1) + sq(y1) - r * (sq(x2) + sq(y2));
	}
	// Translation: x_old = x_new + s,  y_old = y_new + t
	Quad trans(double s, double t) {
		Quad q;
		q.a = a;
		q.b = 2*a*s + b;
		q.c = 2*a*t + c;
		q.d = a*s*s + a*t*t + b*s + c*t + d;
		return q;
	}
};

vector<Point> solve2(Quad q1, Quad q2) {
	// asserts: |q1.a|>=EPS, q1.b=q1.c=0  (i.e q1 is: q1.a (x^2 + y^2) + q1.d = 0)
	vector<Point> res;

	double r2 = -q1.d / q1.a;
	if (r2 < -EPS) return res;
	if (r2 < EPS) {
		if (fabs(q2.eval(0, 0)) < EPS) res.push_back(Point(0, 0));
		return res;
	}

	Line l(q2.b, q2.c, q2.d + q2.a*r2);
	if (dist(l.a, l.b) < EPS) return res;

	Point p = fabs(l.a)>fabs(l.b) ? Point(-l.c/l.a,0) : Point(0,-l.c/l.b);
	Point d(-l.b, l.a);

	double a = dot(d, d), b = 2*dot(p, d), c = dot(p, p) - r2;
	double D = b*b-4*a*c;
	if (D < -EPS) return res;
	if (D < EPS) D = 0; else D = sqrt(D);

	double t = (-b + D) / (2 * a);
	res.push_back(Point(p.x+t*d.x, p.y+t*d.y));

	t = (-b - D) / (2 * a);
	res.push_back(Point(p.x+t*d.x, p.y+t*d.y));

	return res;
}

vector<Point> solve1(Quad q1, Quad q2) {
	if (fabs(q2.a) > fabs(q1.a)) swap(q1, q2);
	if (fabs(q1.a) < EPS) return isect(Line(q1.b, q1.c, q1.d), Line(q2.b, q2.c, q2.d));

	double s = -q1.b / (2 * q1.a), t = -q1.c / (2 * q1.a);
	vector<Point> v = solve2(q1.trans(s, t), q2.trans(s, t));
	for (int i = 0; i < (int)v.size(); i++) {
		v[i].x += s;
		v[i].y += t;
	}
	return v;
}

int main() {
	double x[3], y[3], r[3];
	for (;;) {
		for (int i = 0; i < 3; i++) {
			if (scanf(" %lf %lf %lf", &x[i], &y[i], &r[i]) != 3)
				return 0;
			if (r[i] < EPS) return 0;
		}

		Quad q1; q1.circ(x[0], y[0], r[0], x[1], y[1], r[1]);
		Quad q2; q2.circ(x[0], y[0], r[0], x[2], y[2], r[2]);
		vector<Point> sol = solve1(q1, q2);

		if (sol.size() == 0) {
			printf("No solution\n");
		} else {
			Point best = sol[0];
			double bestr = -1;
			for (int i = 0; i < (int)sol.size(); i++) {
				double rat = r[0] / dist(sol[i].x - x[0], sol[i].y - y[0]);
				if (rat > bestr) { bestr = rat; best = sol[i]; }
			}
			printf("%.2lf %.2lf\n", best.x, best.y);
		}
	}
}
