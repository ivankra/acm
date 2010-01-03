#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <set>
using namespace std;

struct Point {
	int x, y;
};

int sq(int x) {
	return x * x;
}

int dist2(const Point &a, const Point &b) {
	return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

bool byXY(const Point &a, const Point &b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool byYX(const Point &a, const Point &b) {
	return a.y < b.y || (a.y == b.y && a.x < b.x);
}

Point P[10010], Q[10010], bestP;
int N, K, bestDist2;

void rec(int a, int b) {
	if (b-a < 64) {
		for (int i = a; i <= b; i++) {
			for (int j = i+1; j <= b; j++) {
				int t = dist2(P[i], P[j]);
				if (t < bestDist2) {
					bestDist2 = t;
					bestP = P[i];
				}
			}
		}
		return;
	}

	int mid = (a + b) / 2;
	int midX = P[mid].x;

	rec(a, mid);
	rec(mid+1, b);

	K = 0;
	for (int i = a; i <= b; i++) {
		if (sq(P[i].x - midX) < bestDist2)
			Q[K++] = P[i];
	}

	sort(Q, Q+K, byYX);

	for (int i = 0; i < K; i++) {
		for (int j = i+1; j < K && sq(Q[j].y-Q[i].y) < bestDist2; j++) {
			int t = dist2(Q[i], Q[j]);
			if (t < bestDist2) {
				bestDist2 = t;
				bestP = Q[i];
			}
		}
	}
}

int main() {
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d", &N) == 1; cs++) {
		for (int i = 0; i < N; i++)
			scanf("%d %d", &P[i].x, &P[i].y);
		sort(P, P+N, byXY);

		bestDist2 = 0x7fffffff;
		rec(0, N-1);

		if (cs > 1) printf("\n");
		printf("%d.000 %d.000\n", bestP.x, bestP.y);
	}
}
