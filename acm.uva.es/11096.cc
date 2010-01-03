#include <cstdio>
#include <cmath>
#include <algorithm>
typedef long long int64;
using namespace std;

#define EPS 1e-8

struct Point {
	int64 x, y;
	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

int64 cross(const Point &o, const Point &a, const Point &b) {
	return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}

double dist(const Point &a, const Point &b) {
	return sqrt((a.x-b.x)*(double)(a.x-b.x)+(a.y-b.y)*(double)(a.y-b.y));
}

int N;
Point P[1024];

double solve() {
	sort(P, P+N);

	int h[2048], m = 0;

	for (int i = 0; i < N; i++) {
		while (m >= 2 && cross(P[h[m-2]], P[h[m-1]], P[i]) <= 0) m--;
		h[m++] = i;
	}

	for (int i = N-1, t = m-1; i >= 0; i--) {
		while (m-t >= 2 && cross(P[h[m-2]], P[h[m-1]], P[i]) <= 0) m--;
		h[m++] = i;
	}

	double sum = 0;
	for (int i = 0; i < m-1; i++)
		sum += dist(P[h[i]], P[h[i+1]]);
	return sum;
}

int main() {
	int T;
	scanf("%d", &T);

	double len;

	for (int cs = 1; cs <= T; cs++) {
		scanf("%lf %d", &len, &N);
		for (int i = 0; i < N; i++)
			scanf("%lld %lld", &P[i].x, &P[i].y);
		printf("%.5f\n", max(len, solve()));
	}
}
