/*
ID: infnty1
PROB: fc
LANG: C++
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define EPS 1e-9

struct Point {
	double x, y;
	bool operator <(const Point &q) const {
		if (fabs(x - q.x) < EPS) return y < q.y;
		return x < q.x;
	}
} P[10010], Q[10010];

int N;

double cross(const Point &o, const Point &a, const Point &b) {
	return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}

double dist(const Point &a, const Point &b) {
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

int main() {
	freopen("fc.in", "r", stdin);
	freopen("fc.out", "w", stdout);

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%lf %lf", &P[i].x, &P[i].y);
	sort(P, P+N);

	double res = 0;

	for (int pass = 0; pass < 2; pass++) {
		int m = 0;
		for (int i = 0; i < N; i++) {
			Point t = pass==0 ? P[i] : P[N-1-i];
			while (m >= 2 && cross(Q[m-2], Q[m-1], t) < EPS) m--;
			Q[m++] = t;
		}

		for (int i = 0; i < m-1; i++)
			res += dist(Q[i], Q[i+1]);
	}

	printf("%.2lf\n", res);
}
