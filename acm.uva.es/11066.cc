#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define EPS 1e-6

struct Point {
	double x, y;
	bool operator <(const Point &q) const { return x < q.x; }
};

int nc, nm, ne;
Point C[1024], M[1024], E[4096];

int main() {
	while (scanf("%d", &nc) == 1 && nc > 0) {
		for (int i = 0; i < nc; i++) scanf("%lf %lf", &C[i].x, &C[i].y);
		scanf("%d", &nm);
		for (int i = 0; i < nm; i++) scanf("%lf %lf", &M[i].x, &M[i].y);

		ne = 0;
		for (int i = 0; i < nc-1; i++) {
			E[ne].x = C[i].x;
			E[ne].y = -(C[i+1].y-C[i].y)/(C[i+1].x-C[i].x);
			E[ne+1].x = C[i+1].x;
			E[ne+1].y = -E[ne].y;
			ne += 2;
		}

		for (int i = 0; i < nm-1; i++) {
			E[ne].x = M[i].x;
			E[ne].y = (M[i+1].y-M[i].y)/(M[i+1].x-M[i].x);
			E[ne+1].x = M[i+1].x;
			E[ne+1].y = -E[ne].y;
			ne += 2;
		}

		sort(E, E+ne);

		double y0 = M[0].y - C[0].y, x0 = M[0].x, m = 0, res = 0;

		for (int i = 0; i < ne;) {
			if (fabs(x0-E[i].x) < EPS) { m += E[i++].y; continue; }

			double dx = E[i].x - x0;
			double y1 = y0 + m * dx;

			if (y0 > -EPS && y1 > -EPS) {
				res += y0*dx + m*dx*dx/2;
			} else if (y0 > EPS && y1 < -EPS) {
				double c = -y0 / m;
				res += y0*c + m*c*c/2;
			} else if (y0 < -EPS && y1 > EPS) {
				double c = -y0 / m;
				double w = dx - c;
				double yc = y0 + m * c;
				res += yc*w + m*w*w/2;
			}

			y0 = y1;
			x0 = E[i].x;
		}

		if (res < EPS) res = 0.0;
		printf("%.2f\n", res);
	}
}
