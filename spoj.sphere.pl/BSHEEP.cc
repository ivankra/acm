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
using namespace std;

struct Point {
	int x, y, index;
	bool operator <(const Point &other) const {
		if (y != other.y) return y < other.y;
		if (x != other.x) return x < other.x;
		return index < other.index;
	}
};

int cross(const Point &o, const Point &a, const Point &b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

Point P[100010], H[200010];

int main()
{
	int T, N;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		if (cs != 1) printf("\n");

		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &P[i].x, &P[i].y);
			P[i].index = i+1;
		}

		sort(P, P+N);

		int k = 1;
		for (int i = 1; i < N; i++) {
			if (P[i].x != P[i-1].x || P[i].y != P[i-1].y) {
				if (k != i) P[k] = P[i];
				k++;
			}
		}
		N = k;

		k = 0;
		for (int i = 0; i < N; i++) {
			while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
			H[k++] = P[i];
		}

		for (int i = N-1, t = k+1; i >= 0; i--) {
			while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
			H[k++] = P[i];
		}

		k--;

		double len = 0;
		for (int i = 0; i < k; i++) {
			double dx = H[i].x - H[i+1].x;
			double dy = H[i].y - H[i+1].y;
			len += sqrt(dx*dx + dy*dy);
		}
		printf("%.2f\n", len);

		for (int i = 0; i < k; i++) {
			printf(i==0 ? "%d" : " %d", H[i].index);
		}
		printf("\n");
	}
}
