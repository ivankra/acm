/*
ID: infnty1
PROB: fence3
LANG: C++
*/
#include <cstdio>
#include <cmath>
#include <complex>
#include <algorithm>
using namespace std;

typedef complex<double> Point;

struct Fence { Point A, B; } F[500];
int N;

double dot(Point a, Point b) { return (conj(a)*b).real(); }
double cross(Point a, Point b) { return (conj(a)*b).imag(); }

double f(double x, double y) {
	double res = 0;
	Point P(x, y);
	for (int i = 0; i < N; i++) {
		Point &A = F[i].A, &B = F[i].B;
		double d = min(abs(A-P), abs(B-P));
		if (dot(B-A, P-A) > 0 && dot(A-B, P-B) > 0 && abs(A-B) > 1e-6)
			d = min(d, fabs(cross(B-A, P-A) / abs(A-B)));
		res += d;
	}
	return res;
}

int main() {
	freopen("fence3.in", "r", stdin);
	freopen("fence3.out", "w", stdout);

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		double x1, y1, x2, y2;
		scanf(" %lf %lf %lf %lf", &x1, &y1, &x2, &y2);
		F[i].A = Point(x1, y1);
		F[i].B = Point(x2, y2);
	}

	double x = 0, y = 0, z = f(x,y);

	for (double e = 100; e > 1e-4;) {
		int ok = 0;
		for (int dx = -1; dx <= 1; dx += 2)
		for (int dy = -1; dy <= 1; dy += 2) {
			double t = f(x+dx*e, y+dy*e);
			if (t < z-1e-9) {
				z = t;
				x += dx*e;
				y += dy*e;
				ok = 1;
			}
		}
		if (!ok) e /= 2;
	}

	printf("%.1f %.1f %.1f\n", x, y, f(x,y));
}
