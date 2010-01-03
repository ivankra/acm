#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

struct Line {
	int a, b, c;
	Line() {}
	Line(int x1, int y1, int x2, int y2) {
		a = y2 - y1;
		b = x1 - x2;
		c = a * x1 + b * y1;
	}
};

int X[20], Y[20], N, order[20], height, width;
Line lines[20];
int nlines;
double best;

void checkOrder()
{
	double res = 0;

	nlines = 4;

	for (int i = 0; i < N; i++) {
		Line l(X[order[i]], Y[order[i]], X[order[i]+1], Y[order[i]+1]);

		double mid_x = (X[order[i]] + X[order[i]+1]) / 2.0;
		double mid_y = (Y[order[i]] + Y[order[i]+1]) / 2.0;
		double d1 = 1e20, d2 = 1e20;

		for (int j = 0; j < nlines; j++) {
			const Line &m = lines[j];

			int det = l.a * m.b - l.b * m.a;
			if (det == 0) continue;

			double x = (l.c * m.b - l.b * m.c) / (double)det;
			double y = (l.a * m.c - l.c * m.a) / (double)det;

			double dist = sqrt((x - mid_x) * (x - mid_x) + (y - mid_y) * (y - mid_y));
			if (x < mid_x - 1e-9 || (x < mid_x + 1e-9 && y < mid_y)) {
				d1 = min(d1, dist);
			} else {
				d2 = min(d2, dist);
			}
		}

		res += d1 + d2;
		if (res > best) return;

		lines[nlines] = l;
		nlines++;
	}

	if (res < best) best = res;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d %d %d", &width, &height, &N) == 3; cs++) {
		if (width <= 0 || height <= 0) break;
		assert(3 <= N && N <= 8);

		for (int i = N-1; i >= 0; i--) {
			scanf("%d %d", &X[i], &Y[i]);
		}
		X[N] = X[0];
		Y[N] = Y[0];

		lines[0] = Line(0, 0, width, 0);
		lines[1] = Line(width, 0, width, height);
		lines[2] = Line(width, height, 0, height);
		lines[3] = Line(0, height, 0, 0);

		for (int i = 0; i < N; i++)
			order[i] = i;

		best = 1e20;
		do { checkOrder(); } while (next_permutation(order, order+N));

		if (cs != 1) printf("\n");
		printf("Minimum total length = %.3f\n", best);
	}
}
