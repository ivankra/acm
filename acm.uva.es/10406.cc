#include <cstdio>
#include <cassert>
#include <cmath>

enum { MAXN = 10000 };

struct Point { double x, y; } P[MAXN], Q[MAXN];
double D;
int N;

int main()
{
	while (scanf("%lf %d", &D, &N) == 2 && N > 0) {
		assert(N <= MAXN-10);
		for (int i = 0; i < N; i++)
			scanf("%lf %lf", &P[i].x, &P[i].y);

		P[N] = P[0];
		P[N+1] = P[1];

		for (int i = 0; i < N; i++) {
			double a1 = P[i+1].y - P[i].y;
			double b1 = P[i].x - P[i+1].x;
			double t = sqrt(a1 * a1 + b1 * b1);
			a1 /= t;
			b1 /= t;
			double c1 = a1 * P[i].x + b1 * P[i].y + D;

			double a2 = P[i+2].y - P[i+1].y;
			double b2 = P[i+1].x - P[i+2].x;
			t = sqrt(a2 * a2 + b2 * b2);
			a2 /= t;
			b2 /= t;
			double c2 = a2 * P[i+1].x + b2 * P[i+1].y + D;

			double det = a1 * b2 - a2 * b1;
			Q[i].x = (c1 * b2 - c2 * b1) / det;
			Q[i].y = (a1 * c2 - a2 * c1) / det;
		}

		Q[N] = Q[0];

		double area = 0;
		for (int i = 0; i < N; i++)
			area += Q[i].x * Q[i+1].y - Q[i+1].x * Q[i].y;
		area = fabs(area / 2);

		printf("%.3lf\n", area);
	}
}
