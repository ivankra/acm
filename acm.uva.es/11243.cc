#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

struct Point {
	double x, y;
};

Point P[50];
int N;

double PI = 2 * acos(0.0);

double f(double theta)
{
	double sin_t = sin(-theta), cos_t = cos(-theta);

	double min_x = 1e10, max_x = -1e10;
	double min_y = 1e10, max_y = -1e10;
	for (int i = 0; i < N; i++) {
		double x = P[i].x * cos_t - P[i].y * sin_t;
		min_x <?= x; max_x >?= x;

		double y = P[i].x * sin_t + P[i].y * cos_t;
		min_y <?= y; max_y >?= y;
	}

	return max(max_x - min_x, max_y - min_y);
}

double ternary(double a, double b)
{
	double fa = f(a), fb = f(b);
	double res = min(fa, fb);

	for (int iter = 0; iter < 20; iter++) {
		double u = (2 * a + b) / 3, fu = f(u);
		double v = (a + 2 * b) / 3, fv = f(v);
		res <?= fu; res <?= fv;

		if (fu > fv) { a = u; fa = fu; }
		else { b = v; fb = fv; }
	}

	return res;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			 scanf("%lf %lf", &P[i].x, &P[i].y);

		double best = 1e20;
		for (double x = 0; x < PI/2; x += 0.001)
			best <?= ternary(x, x+0.001);
		printf("%.2f\n", best*best);
	}
}
