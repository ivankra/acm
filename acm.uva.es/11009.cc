#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <algorithm>
using namespace std;

struct Point {
	double x, y;
	Point(double X, double Y) : x(X), y(Y) { }

	double abs() {
		return sqrt(x*x + y*y);
	}

	void norm() {
		double t = abs();
		x /= t;
		y /= t;
	}
};

double cos30 = sqrt(3.0) / 2.0;

bool possible(double a, double b, double s) {
	Point A(a/2 + b, -cos30 * a);
	Point B(a/2 + b - sqrt(3.0*max(0.0, s*s-a*a)), cos30 * a);
	if (B.x < a/2) return false;

	Point C((A.x+B.x)/2, (A.y+B.y)/2);

	Point v(B.x-A.x, B.y-A.y);
	v.norm();
	if (v.y < 0) { v.x = -v.x; v.y = -v.y; }

	Point G(C.x - v.y * s/2, C.y + v.x * s/2);
	return G.x > 0 && G.abs() > cos30*s;
}

double solve(double a, double b) {
	double left = a, right = a+a;
	for (int k = 0; k < 50 && right - left > 1e-9; k++) {
		double middle = (left + right) / 2;
		if (possible(a, b, middle))
			left = middle;
		else
			right = middle;
	}
	return left;
}

int main() {
	int ai, start, end;
	while (scanf(" %d %d %d", &ai, &start, &end) == 3 && ai > 0) {
		double res = 0;
		for (int i = start; i <= end; i++)
			res += solve(ai, ai+i);

		if (fabs(res - floor(res)) < fabs(res - ceil(res)))
			res = floor(res);
		else
			res = ceil(res);
		printf("%.0f\n", res);
	}
}
