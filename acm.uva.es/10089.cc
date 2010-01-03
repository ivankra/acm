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
typedef long long LL;

struct Point {
	LL x, y;
	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

int cross(const Point &o, const Point &a, const Point &b)
{
	LL t = (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
	if (t == 0) return 0;
	return t > 0 ? 1 : -1;
}

Point P[5000], H[5000];
int N, K;

bool solve()
{
	for (int i = 0; i < N; i++) {
		if (P[i].x == 0 && P[i].y == 0) return true;
	}

	sort(P, P+N);

//printf("P:");for (int i = 0; i < N; i++) printf(" (%lld,%lld)",P[i].x,P[i].y);printf("\n");

	K = 0;
	for (int i = 0; i < N; i++) {
		while (K >= 2 && cross(H[K-2], H[K-1], P[i]) <= 0)
			K--;
		H[K++] = P[i];
	}

	for (int i = N-1, t = K; i >= 0; i--) {
		while (K >= t+2 && cross(H[K-2], H[K-1], P[i]) <= 0)
			K--;
		H[K++] = P[i];
	}

	Point O = { 0, 0 };
	for (int i = 0; i < K-1; i++) {
		if (cross(O, H[i], H[i+1]) < 0) return false;
	}

	return true;
}

int main()
{
	while (scanf("%d", &N) == 1 && N > 0) {
		for (int i = 0; i < N; i++) {
			long long a, b, c;
			scanf("%lld %lld %lld", &a, &b, &c);
			P[i].x = a - b;
			P[i].y = b - c;
		}
		printf(solve() ? "Yes\n" : "No\n");
	}
}
