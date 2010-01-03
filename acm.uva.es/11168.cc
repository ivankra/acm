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
	int x, y;

	bool operator <(const Point &other) const {
		return x < other.x || (x == other.x && y < other.y);
	}
};

int cross(const Point &o, const Point &a, const Point &b) {
	long long t = (a.x - o.x) * (long long)(b.y - o.y);
	t -= (a.y - o.y) * (long long)(b.x - o.x);
	return t == 0 ? 0 : (t > 0 ? 1 : -1);
}

vector<Point> convexHull(vector<Point> P)
{
	int N = P.size();
	sort(P.begin(), P.end());

	vector<Point> H(2*N);
	int K = 0;

	for (int i = 0; i < N; i++) {
		while (K >= 2 && cross(H[K-2], H[K-1], P[i]) <= 0) K--;
		H[K++] = P[i];
	}

	for (int i = N-1, t = K+1; i >= 0; i--) {
		while (K >= t && cross(H[K-2], H[K-1], P[i]) <= 0) K--;
		H[K++] = P[i];
	}

	H.resize(K-1);
	return H;
}

double solve(const vector<Point> &pts)
{
	vector<Point> H = convexHull(pts);
	int N = pts.size(), K = H.size();

	double Xavg = 0, Yavg = 0;
	for (int i = 0; i < N; i++) {
		Xavg += pts[i].x;
		Yavg += pts[i].y;
	}
	Xavg /= N;
	Yavg /= N;

	double best = 1e20;

	for (int i = 0; i < K; i++) {
		int j = (i + 1) % K;
		double a = H[i].y - H[j].y;
		double b = H[j].x - H[i].x;
		double t = sqrt(a*a + b*b);
		a /= t;
		b /= t;
		double c = -(a * H[i].x + b * H[i].y);

		best = min(best, a * Xavg + b * Yavg + c);
	}

	double alpha = atan2(-Xavg, Yavg);
	double a = -sin(alpha);
	double b = cos(alpha);

	for (int i = 0; i < K; i++) {
		int j = (i + 1) % K;
		int k = (i + 2) % K;
		double c = -(a * H[j].x + b * H[j].y);

		double v1 = a * H[i].x + b * H[i].y + c;
		double v2 = a * H[k].x + b * H[k].y + c;
		if (v1 > -1e-6 && v2 > -1e-6) {
			best = min(best, a * Xavg + b * Yavg + c);
		}
	}

	if (fabs(best) < 1e-4) best = 0.0;
	return best;
}

int main()
{
	int T, N;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);
		vector<Point> P(N);
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &P[i].x, &P[i].y);
		}
		printf("Case #%d: %.3f\n", cs, solve(P));
	}
}
