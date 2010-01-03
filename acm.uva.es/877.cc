#include <cstdio>
#include <cassert>
#include <cmath>

struct Point { double x, y; } P[50], Q[50];
double D;
int N;

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%lf %d", &D, &N);
		assert(3 <= N && N <= 8);
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
			double c1 = a1 * P[i].x + b1 * P[i].y - D;

			double a2 = P[i+2].y - P[i+1].y;
			double b2 = P[i+1].x - P[i+2].x;
			t = sqrt(a2 * a2 + b2 * b2);
			a2 /= t;
			b2 /= t;
			double c2 = a2 * P[i+1].x + b2 * P[i+1].y - D;

			double det = a1 * b2 - a2 * b1;
			Q[i].x = (c1 * b2 - c2 * b1) / det;
			Q[i].y = (a1 * c2 - a2 * c1) / det;
		}

		printf("%d\n", N);
		for (int i = 0; i < N; i++) {
			int j = (i+N-1)%N;
			if (fabs(Q[j].x) < 5e-4) Q[j].x = 0;
			if (fabs(Q[j].y) < 5e-4) Q[j].y = 0;
			printf("%.3lf %.3lf\n", Q[j].x, Q[j].y);
		}
		if (cs != T) printf("\n");
	}
}
