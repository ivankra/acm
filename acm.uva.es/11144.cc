#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

struct Point {
	long long x, y;
	Point(long long X, long long Y) : x(X), y(Y) {}
};

double dist(const Point &a, const Point &b) {
	return sqrt((a.x-b.x)*(double)(a.x-b.x) + (a.y-b.y)*(double)(a.y-b.y));
}

double linedist(const Point &p, const Point &a, const Point &b) {
	if (((b.x-a.x)*(p.x-a.x) + (b.y-a.y)*(p.y-a.y)) < 0) return 1e99;
	if (((a.x-b.x)*(p.x-b.x) + (a.y-b.y)*(p.y-b.y)) < 0) return 1e99;
	if (dist(a, b) < 1e-8) return 1e99;

	double S2 = fabs((a.x-p.x)*(b.y-p.y)-(a.y-p.y)*(b.x-p.x)+0.0);
	return S2 / dist(a, b);
}

double dist(const vector<Point> &P, const vector<Point> &Q) {
	int N = P.size()-1, M = Q.size()-1;
	double res = 1e99;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			res <?= dist(P[i], Q[j]);
			res <?= linedist(P[i], Q[j], Q[j+1]);
			res <?= linedist(Q[j], P[i], P[i+1]);
		}
	}

	return res;
}

long long area2(const vector<Point> &P) {
	long long s = 0;
	for (int i = 0, n = P.size()-1; i < n; i++)
		s += P[i].x * P[i+1].y - P[i].y * P[i+1].x;
	return s < 0 ? -s : s;
}

int main()
{
	int T, N;
	long long d[128][128];
	vector<Point> P[128];

	for (scanf("%d", &T); T--;) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			int L; long long x, y;
			scanf("%d", &L);
			P[i].clear();
			for (int j = 0; j < L; j++) {
				scanf("%lld %lld", &x, &y);
				P[i].push_back(Point(x, y));
			}
			P[i].push_back(P[i][0]);
		}

		long long ar[128];
		for (int i = 0; i < N; i++)
			ar[i] = area2(P[i]);

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				d[i][j] = (i == j) ? 0 : (1LL<<20);

		for (int i = 0; i < N; i++) {
			for (int j = i+1;j < N; j++) {
				//printf("dist(%d,%d) = %.5f\n", i,j,dist(P[i],P[j]));
				if (dist(P[i], P[j]) < 30.0 - 1e-8) {
					d[i][j] = (ar[j]*10 + ar[i]-1) / ar[i];
					d[j][i] = (ar[i]*10 + ar[j]-1) / ar[j];
					//printf("%d -> %d  %lld\n", i, j, d[i][j]);
					//printf("%d -> %d  %lld\n", j, i, d[j][i]);
				}
			}
		}

		for (int k = 0; k < N; k++)
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					d[i][j] <?= d[i][k] + d[k][j];

		int s; long long e;
		scanf("%d %lld", &s, &e);

		for (int x = 0, k = 0; x < N; x++)
			if (d[s][x] <= e) printf(k++ ? " %d" : "%d", x);
		printf("\n");
	}
}
