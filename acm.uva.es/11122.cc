#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long int64;

struct Point {
	int64 x, y;
};

double EPS = 1e-9;

struct dPoint {
	double x, y;
	dPoint(double X, double Y) : x(X), y(Y) {}
};

int64 cross(const Point &o, const Point &a, const Point &b) {
	return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}

double dcross(const dPoint &o, const dPoint &a, const dPoint &b) {
	return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}

// Does point p lie on segment ab?
bool liesOn(const Point &p, const Point &a, const Point &b) {
	if (cross(p, a, b) != 0) return false;

	return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
	       min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

// Is point p inside or on boundary of triangle t?
bool inside(const Point &p, Point t[]) {
	if (cross(p, t[0], t[1]) >= 0 &&
	    cross(p, t[1], t[2]) >= 0 &&
	    cross(p, t[2], t[0]) >= 0)
		return true;

	if (cross(p, t[0], t[1]) <= 0 &&
	    cross(p, t[1], t[2]) <= 0 &&
	    cross(p, t[2], t[0]) <= 0)
		return true;

	return false;
}

// Is point p strictly inside triangle t?
bool strictlyInside(const Point &p, Point t[]) {
	if (cross(p, t[0], t[1]) > 0 &&
	    cross(p, t[1], t[2]) > 0 &&
	    cross(p, t[2], t[0]) > 0)
		return true;

	if (cross(p, t[0], t[1]) < 0 &&
	    cross(p, t[1], t[2]) < 0 &&
	    cross(p, t[2], t[0]) < 0)
		return true;

	return false;
}

int64 llabs(int64 x) { return x < 0 ? -x : x; }

bool solve(Point A[], Point B[]) {
	for (int i = 0; i < 3; i++)
		if (strictlyInside(A[i], B)) return true;

	bool ok = true;
	for (int i = 0; i < 3; i++)
		if (!inside(A[i], B)) ok = false;
	if (ok) return true;

	vector<dPoint> pt;
	for (int i = 0; i < 3; i++) {
		if (inside(A[i], B)) pt.push_back(dPoint(A[i].x, A[i].y));
		if (inside(B[i], A)) pt.push_back(dPoint(B[i].x, B[i].y));
	}

	for (int i = 0; i < 3; i++) {
		Point &a = A[i];
		Point &b = A[(i+1)%3];

		for (int j = 0; j < 3; j++) {
			Point &c = B[j];
			Point &d = B[(j+1)%3];

			// a + (b-a)t = c + (d-c)s    0<=t<=1 0<=s<=1
			// (b-a)t + (c-d)s = c -a

			long long a1 = b.x-a.x, b1 = c.x-d.x, c1 = c.x-a.x;
			long long a2 = b.y-a.y, b2 = c.y-d.y, c2 = c.y-a.y;

			long long det = a1 * b2 - a2 * b1;
			if (det == 0) continue;

			long long sn = c1 * b2 - c2 * b1;
			if ((sn < 0 && det > 0) || (sn > 0 && det < 0)) continue;
			if (llabs(sn) > llabs(det)) continue;

			long long tn = a1 * c2 - a2 * c1;
			if ((tn < 0 && det > 0) || (tn > 0 && det < 0)) continue;
			if (llabs(tn) > llabs(det)) continue;

			double s = sn / (double)det;
			pt.push_back(dPoint(a.x+(b.x-a.x)*s, a.y+(b.y-a.y)*s));
		}
	}

/*	printf("pt=");
	for (int  i = 0; i < (int)pt.size();i++)
		printf("(%.3f, %.3f)  ", pt[i].x, pt[i].y);
		printf("\n");
*/
	for (int i = 0; i < (int)pt.size(); i++) {
		for (int j = i+1; j < (int)pt.size(); j++) {
			for (int k = j+1; k < (int)pt.size(); k++) {
				if (fabs(dcross(pt[i], pt[j], pt[k])) > 1e-8)
					return true;
			}
		}
	}


	return false;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		Point tri[2][3];
		for (int k = 0; k < 2; k++)
			for (int i = 0; i < 3; i++)
				scanf("%lld %lld", &tri[k][i].x, &tri[k][i].y);

		printf("pair %d: ", cs);
		if (solve(tri[0], tri[1]) || solve(tri[1], tri[0]))
			printf("yes\n");
		else
			printf("no\n");
	}
}