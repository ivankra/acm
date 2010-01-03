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
#include <queue>
using namespace std;

struct Point {
	int x, y;
	bool operator <(const Point &p) const { return x < p.x || (x == p.x && y < p.y); }
} P[2000];

int main() {
	int T, N, width, height;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d %d", &width, &height) == 2; cs++) {
		int K, x, y, dx, dy;
		N = 0;
		while (scanf("%d", &K) == 1 && K > 0) {
			scanf("%d %d", &x, &y);
			if (K > 1) scanf("%d %d", &dx, &dy);
			for (; K >= 1; K--) {
				P[N].x = x; P[N].y = y; N++;
				x += dx; y += dy;
			}
		}

		int best = (N == 0 ? width*height : 0);
		for (int rot = 0; rot < 4; rot++) {
			sort(P, P+N);

			for (int s = 0; s < N; s++) {
				int high = height, low = 0;
				for (int t = s+1; t < N; t++) {
					if (P[t].x == P[s].x) continue;
					best = max(best, (high - low) * (P[t].x - P[s].x));
					if (t == N || P[t].y == P[s].y) {
						low = high = P[s].y;
						break;
					} else if (P[t].y > P[s].y) {
						high = min(high, P[t].y);
					} else {
						low = max(low, P[t].y);
					}
				}
				best = max(best, (high - low) * (width - P[s].x));
			}

			for (int i = 0; i < N; i++) {
				int y1 = P[i].x, x1 = height - P[i].y;
				P[i].x = x1; P[i].y = y1;
			}
			swap(width, height);
		}

		printf("%d\n", best);
	}
}
