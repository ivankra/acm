#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
double hyp(double x, double y) { return sqrt(x*x+y*y); }

double pi=2*acos(0.0), gap=0.01*pi/180.0, xo, yo, radii;
int res;

bool between(double a, double x, double b) { return a < x && x < b; }

bool visible(int ax, int ay) {
	double ad = asin(radii/hyp(ax-xo, ay-yo));
	if (2*ad < gap) return false;

	double ac = atan2(ay-yo, ax-xo);
	double al = ac + ad;
	double ar = ac - ad;

	for (int by = 1; by <= ay+2; by++) {
		for (int bx = 1; bx <= ax+2; bx++) {
			if (bx*bx+by*by >= ax*ax+ay*ay) break;

			double bc = atan2(by-yo, bx-xo);
			double bd = asin(radii/hyp(bx-xo, by-yo)) + gap;
			double bl = bc + bd, br = bc - bd;

			if (between(br, al, bl)) return false;
			if (between(br, ar, bl)) return false;

			if (between(ar, bl, al)) return false;
			if (between(ar, br, al)) return false;
		}
	}

	return true;
}

void countOnQuarterPlane() {
	for (int x = 1; x <= 20; x++)
		for (int y = 1; y <= 20; y++)
			if (visible(x, y)) res++;
}

int main() {
	double x, y, d;
	while (scanf("%lf %lf %lf", &d, &x, &y) == 3 && d > 0.05) {
		res = 0;
		for (int k = 0; k < 4; k++) {
			xo = (k & 1) ? 1-x : x;
			yo = (k & 2) ? 1-y : y;
			radii = d/2;
			countOnQuarterPlane();
		}
		printf("%d\n", res);
	}
}
