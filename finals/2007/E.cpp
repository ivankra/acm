// ACM ICPC World Finals 2007
// Problem E. Collecting Luggage.
// Algorithm: binary search + shortest path on plane (visibility graph)
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

double INF = 1.0 / 0.0;

struct Point {
	double x, y;

	double distTo(const Point &p) const {
		return sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y));
	}

	double cross(const Point &a, const Point &b) const {
		return (a.x - x) * (b.y - y) - (a.y - y) * (b.x - x);
	}

	bool between(const Point &a, const Point &b) const {
		if (fabs(cross(a, b)) > 1e-6) return false;

		return min(a.x, b.x) - 1e-6 < x && x < max(a.x, b.x) + 1e-6 &&
		       min(a.y, b.y) - 1e-6 < y && y < max(a.y, b.y) + 1e-6;
	}
};

Point P[128];
int N;
double VL, VP;

bool inside(Point p) {
	bool flag = false;
	for (int a = 0; a < N; a++) {
		int b = a + 1;
		if (b == N) b = 0;
		if (fabs(P[a].y - P[b].y) < 1e-6) continue;

		double x = P[a].x + (P[b].x - P[a].x) * (p.y - P[a].y) / (P[b].y - P[a].y);
		if (x < p.x) continue;

		double y1 = min(P[a].y, P[b].y);
		double y2 = max(P[a].y, P[b].y);

		if (fabs(y2 - p.y) < 1e-6) continue;
		if (fabs(y1 - p.y) < 1e-6) { flag = !flag; continue; }
		if (y1 < p.y && p.y < y2) flag = !flag;
	}
	return flag;
}

bool visible(int s, int t) {
	for (int a = 0; a < N; a++) {
		int b = (a + 1) % N;
		if (P[s].between(P[a], P[b]) && P[t].between(P[a], P[b])) return true;
	}

	for (int a = 0; a < N; a++) {
		if (a != s && a != t && P[a].between(P[s], P[t])) {
			if (P[a].distTo(P[s]) > 1e-6 && P[a].distTo(P[t]) > 1e-6)
				return false;
		}

		int b = a + 1;
		if (b == N) b = 0;

		if (P[a].cross(P[s], P[t]) * P[b].cross(P[s], P[t]) < -1e-6 &&
		    P[s].cross(P[a], P[b]) * P[t].cross(P[a], P[b]) < -1e-6) {
			return false;
		}
	}

	Point mid;
	mid.x = (P[s].x + P[t].x) / 2;
	mid.y = (P[s].y + P[t].y) / 2;
	if (inside(mid)) return false;

	return true;
}

bool check(double tm, bool first) {
	double cycle = 0;
	for (int i = 0; i < N; i++)
		cycle += P[i].distTo(P[(i+1)%N]);

	double t = fmod(tm*VL, cycle);
	for (int i = 0;;) {
		int j = (i + 1) % N;
		double a = P[i].distTo(P[j]);
		if (t >= a) {
			t -= a;
			i = j;
		} else {
			P[N+1].x = P[i].x * (1-t/a) + P[j].x * t/a;
			P[N+1].y = P[i].y * (1-t/a) + P[j].y * t/a;
			break;
		}
	}

	static double adj[128][128];

	if (first) {
		for (int i = 0; i <= N+1; i++) {
			adj[i][i] = 0;
			for (int j = i+1; j <= N+1; j++)
				adj[i][j] = adj[j][i] = (visible(i, j) ? P[i].distTo(P[j]) : INF);
		}
	} else {
		for (int i = 0; i <= N; i++)
			adj[i][N+1] = adj[N+1][i] = (visible(i, N+1) ? P[i].distTo(P[N+1]) : INF);
	}

	double dist[128];
	bool seen[128];

	for (int i = 0; i <= N+1; i++) { dist[i] = INF; seen[i] = false; }

	dist[N] = 0;
	while (true) {
		int u = -1;
		for (int i = 0; i <= N+1; i++)
			if (!seen[i] && (u < 0 || dist[i] < dist[u])) u = i;
		if (u < 0 || dist[u] > 1e20) break;

		seen[u] = true;
		for (int v = 0; v <= N+1; v++)
			dist[v] <?= dist[u] + adj[u][v];
	}
	return dist[N+1]/VP < tm+1e-6;
}

int main()
{
	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		for (int i = 0; i < N; i++)
			scanf("%lf %lf", &P[i].x, &P[i].y);
		scanf("%lf %lf", &P[N].x, &P[N].y);
		scanf("%lf %lf", &VL, &VP);

		double left = 0, right = 2100000;
		bool first = true;
		while ((right - left) * 60 > 0.01) {
			double mid = (left + right) / 2;
			if (check(mid, first))
				right = mid;
			else
				left = mid;
			first = false;
		}

		int t = (int)(left * 60 + 0.5);
		printf("Case %d: Time = %d:%.2d\n", cs, t/60, t%60);
	}	
}
