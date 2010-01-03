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
typedef long long ll;

struct Point {
	ll x, y;
	bool operator <(const Point &p) const {
		return x < p.x;
	}
};

Point P[200];
int N;

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%lld %lld", &P[i].x, &P[i].y);
			assert(0 <= P[i].x && 0 <= P[i].y);
		}
		sort(P, P+N);
		assert(P[0].x == 0 && P[N-1].y == 0);

		double res = 0;
		int y_low = 0;
		for (int i = N-1; i >= 1; i--) {
			assert(P[i].y <= y_low);
			if (P[i-1].y <= y_low) continue;
			int x1 = P[i-1].x;
			int y1 = P[i-1].y;
			int y2 = P[i].y;
			int x2 = P[i].x;
			double y = y_low;
			double x = x1 + (x2-x1)*(y-y1+0.0)/(y2-y1+0.0);
			res += sqrt((x-x1)*(x-x1) + (y-y1)*(y-y1));
			y_low = P[i-1].y;
		}
		printf("%.2f\n", res);
	}
}
