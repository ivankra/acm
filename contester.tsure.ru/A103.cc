#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

struct Point {
	long long x, y;
	Point(long long x=0, long long y=0) : x(x), y(y) {}
	Point operator +(const Point &p) const { return Point(x+p.x,y+p.y); }
	Point operator -(const Point &p) const { return Point(x-p.x,y-p.y); }
	bool operator ==(const Point &p) const { return x==p.x && y==p.y; }
} P[1024];
long long W, H;
int N;

long long cross(const Point &o, const Point &a, const Point &b) {
	return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}

int solve() {
	if (N <= 1) return 0;
	for (int i = 1; i < N-1; i++)
		if (P[i].x<=0 || P[i].x>=W || P[i].y<=0 || P[i].y>=H) return 0;

	for (int di = 0; di < N-1; di++) {
		Point D = P[di+1] - P[di];
		if (D.x == 0 && D.y == 0) continue;

		int i;
		for (i = 0; i < N-1; i++)
			if (cross(P[i], P[i]+D, P[i+1]) < 0) break;
		if (i == N-1) return 1;
	}

	return 0;
}

int main()
{
	while (scanf(" %lld %lld %d", &W, &H, &N) == 3) {
		assert(1 <= W && 1 <= H && 2 <= N && N <= 250);
		for (int i = 0; i < N; i++) {
			int k = scanf("%lld %lld", &P[i].x, &P[i].y);
			assert(k == 2);
		}
		printf(solve() ? "yes\n" : "no\n");
break;
	}
}
