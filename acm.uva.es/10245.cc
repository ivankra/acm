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
	double x, y;
};

double sq(double x) {
	return x * x;
}

double dist(const Point &a, const Point &b) {
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

bool byXY(const Point &a, const Point &b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool byYX(const Point &a, const Point &b) {
	return a.y < b.y || (a.y == b.y && a.x < b.x);
}

Point P[10010], Q[10010];
int N, K;
double best;

void rec(int a, int b) {
	if (b-a < 64) {
		for (int i = a; i <= b; i++)
			for (int j = i+1; j <= b; j++)
				best <?= dist(P[i], P[j]);
		return;
	}

	int mid = (a + b) / 2;
	double midX = P[mid].x;

	rec(a, mid);
	rec(mid+1, b);

	K = 0;
	for (int i = a; i <= b; i++)
		if (sq(P[i].x - midX) < best) Q[K++] = P[i];

	sort(Q, Q+K, byYX);

	for (int i = 0; i < K; i++)
		for (int j = i+1; j < K && sq(Q[j].y-Q[i].y) < best; j++)
			best <?= dist(Q[i], Q[j]);
}

int main() {
	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		for (int i = 0; i < N; i++)
			scanf("%lf %lf", &P[i].x, &P[i].y);
		sort(P, P+N, byXY);

		best = 1e99;
		rec(0, N-1);

		if (best < 10000-1e-4)
			printf("%.4f\n", best);
		else
			printf("INFINITY\n");
	}
}
