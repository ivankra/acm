#include <cstdio>
#include <cassert>
#include <cmath>
#include <algorithm>
using namespace std;

#define EPS 1e-6

double sq(double x) { return x*x; }

double circ(double r, double d) {
	d = fabs(d);
	if (d >= r) return 0;
	return acos(d/r)*r*r - sqrt(r*r-d*d)*d;
}

double squ(double a, double x0, double y0) {
	x0 = fabs(x0); y0 = fabs(y0);
	if (fabs(x0-a/2) < EPS) return 0;
	if (fabs(y0-a/2) < EPS) return 0;

	if (y0 > x0) swap(x0, y0);

	assert(0.0 <= y0 && y0 <= x0 && x0 < a/2);

	double res = a*a/2;	// cut through center

	// vertical/horizontal cuts
	res <?= a*(a/2-x0);
	res <?= a*(a/2-y0);

	// cuts through corners
	for (int t = 0; t < 4; t++) {
		double p = a/2 + x0 * ((t&1)==1 ? 1 : -1);
		double q = a/2 + y0 * ((t&2)==2 ? 1 : -1);
		res <?= p*q/2 * sq(a/max(p,q));
	}

	// triangle case
	res <?= (a/2-x0)*(a/2-y0)*2;

	return res;
}

int main() {
	char s[1024];
	int T;

	while (gets(s) && sscanf(s, "%d", &T) != 1);

	while (T > 0 && gets(s)) {
		double a, b, c, d;
		int k = sscanf(s, "%lf %lf %lf %lf", &a, &b, &c, &d);
		if (k == 4)
			T--, printf("%.3f\n", b*squ(a, c, d));
		else if (k == 3)
			T--, printf("%.3f\n", b*circ(a, c));
	}
}
