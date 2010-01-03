#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

struct Point {
	double x, y, z;
};

double dist(Point a, Point b) {
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	double dz = a.z - b.z;
	return sqrt(dx*dx + dy*dy + dz*dz);
}

#if 1
double area(Point o, Point a, Point b)
{
	a.x -= o.x; a.y -= o.y; a.z -= o.z;
	b.x -= o.x; b.y -= o.y; b.z -= o.z;
	double x = (a.y*b.z - a.z*b.y);
	double y = -(a.x*b.z - a.z*b.x);
	double z = (a.x*b.y - a.y*b.x);
	return sqrt(max(x*x+y*y+z*z, 0.0))/2;
}
#else
double area(Point A, Point B, Point C)
{
	double a = dist(A, B);
	double b = dist(B, C);
	double c = dist(A, C);
	double p = (a+b+c)/2;
	double s = sqrt(max(p*(p-a)*(p-b)*(p-c),0.0));
	return s;
}
#endif

int M, N;
double Down[32][32], Right[32][32];
double dp[22][22][22][22];

int main()
{
	Point P[50], Q[50];
	double z2;
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d %lf", &M, &N, &z2);

		for (int i = 0; i < M; i++) {
			scanf("%lf %lf", &P[i].x, &P[i].y);
			P[i].z = 0;
		}

		for (int i = 0; i < N; i++) {
			scanf("%lf %lf", &Q[i].x, &Q[i].y);
			Q[i].z = z2;
		}

		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				Down[i][j] = area(P[i], P[(i+1)%M], Q[j]);
				Right[i][j] = area(P[i], Q[j], Q[(j+1)%N]);
			}
		}

		for (int m = 0; m <= M; m++) {
			for (int n = 0; n <= N; n++) {
				for (int i = 0; i < M; i++) {
					for (int j = 0; j < N; j++) {
						double &res = dp[m][n][i][j];
						res = 1e20;
						if (m == 0 && n == 0) { res = 0; continue; }
						if (m > 0) res <?= dp[m-1][n][(i+1)%M][j] + Down[i][j];
						if (n > 0) res <?= dp[m][n-1][i][(j+1)%N] + Right[i][j];
					}
				}
			}
		}

		double best = 1e20;
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				best = min(best, dp[M][N][i][j]);
		printf("%.5f\n", best);
	}
}
