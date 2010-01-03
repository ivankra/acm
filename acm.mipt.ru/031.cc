#include <cstdio>
#include <cmath>

double x[200], y[200], z[200];
int n;

double sq(double x0) { return x0 * x0; }

double f(double x0, double y0) {
	double res = 0;
	for (int i = 0; i < n; i++)
		res += z[i] * sqrt(sq(x0-x[i]) + sq(y0-y[i]));
	return res;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%lf %lf %lf", &x[i], &y[i], &z[i]);

	double x0 = 0, y0 = 0;
	for (double step = 256; step > 1e-4; step /= 2) {
		for (int i = 0; i < 100; i++) {
			for (int d = 0; d < 9; d++) {
				double dx = ((d/3)-1)*step;
				double dy = ((d%3)-1)*step;
				while (f(x0+dx, y0+dy) < f(x0, y0))
					x0 += dx, y0 += dy;
			}
		}
	}

	printf("%.2f %.2f\n", x0, y0);
}
