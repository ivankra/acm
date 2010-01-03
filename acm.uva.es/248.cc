#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <vector>
#include <algorithm>
#include <deque>
#include <iostream>
#include <set>
#include <map>
using namespace std;
#define FOREACH(it,v) for(__typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

double EPS = 1e-9;

struct Point {
	double x, y;
	Point() {}
	Point(double xx, double yy) : x(xx), y(yy) {}
	bool operator <(const Point &p) const {
		return x == p.x ? (y < p.y) : (x < p.x);
	}
};

Point operator -(const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator +(const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
double dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
double dist(const Point &a, const Point &b) { return sqrt(dot(a-b, a-b)); }

struct Rect {
	Point p[5];

	void solve() {
		sort(p, p + 3);
		while (true) {
			if (fabs(dot(p[0] - p[1], p[2] - p[1])) < EPS) break;
			assert(next_permutation(p, p + 3));
		}
		p[3] = p[0] + p[2] - p[1];
		p[4] = p[0];

		double area = 0;
		for (int i = 0; i < 4; i++)
			area += p[i].x * p[i+1].y - p[i+1].x * p[i].y;
		if (area < 0) {
			reverse(p, p + 4);
			p[4] = p[0];
		}
	}

	bool inside(Point q) {
		for (int i = 0; i < 4; i++) {
			double cross = (p[i].x - q.x) * (p[i+1].y - q.y) - (p[i+1].x - q.x) * (p[i].y - q.y);
			if (cross < EPS) return false;
		}
		return true;
	}
};

Rect rect[100];
int RN;

bool same(Point &A, Point &B) { return fabs(A.x-B.x) < EPS && fabs(A.y-B.y) < EPS; }

bool visible(Point A, Point B)
{
	vector<double> w;
	w.push_back(0);
	w.push_back(1);

	for (int i = 0; i < RN; i++) {
		for (int j = 0; j < 4; j++) {
			Point C = rect[i].p[j];
			Point D = rect[i].p[j+1];

			if (same(A,C) || same(A,D) || same(B,C) || same(B,D)) continue;

			// (B-A)t + (C-D)s = C-A
			double a1 = B.x-A.x, b1=C.x-D.x, c1=C.x-A.x;
			double a2 = B.y-A.y, b2=C.y-D.y, c2=C.y-A.y;
			double det = a1*b2 - a2*b1;
			if (fabs(det) < EPS) continue;

			double t = (c1*b2 - c2*b1) / det;
			double s = (a1*c2 - a2*c1) / det;
			if (t < EPS || t > 1-EPS) continue;
			if (fabs(s) < EPS || fabs(s - 1) < EPS) w.push_back(t);
			if (s < EPS || s > 1-EPS) continue;

			return false;
		}
	}

	sort(w.begin(), w.end());

	for (int j = 1; j < (int)w.size(); j++) {
		if (fabs(w[j] - w[j-1]) < EPS) continue;
		double t = (w[j] + w[j-1]) / 2;
		Point M(A.x + (B.x-A.x)*t, A.y + (B.y-A.y)*t);
		for (int i = 0; i < RN; i++) {
			if (rect[i].inside(M)) return false;
		}
	}

//printf("A=%.2f,%.2f  B=%.2f,%.2f\n", A.x, A.y, B.x,B.y);

	return true;
}

int main()
{
	double G[128][128];
	int GN;
	Point V[128];

	for (int cs = 1; scanf("%d", &RN) == 1 && RN >= 0; cs++) {
		scanf("%lf %lf %lf %lf", &V[0].x, &V[0].y, &V[1].x, &V[1].y);
		for (int i = 0; i < RN; i++) {
			for (int j = 0; j < 3; j++)
				scanf("%lf %lf", &rect[i].p[j].x, &rect[i].p[j].y);
			rect[i].solve();

			for (int j = 0; j < 4; j++)
				V[2+4*i+j] = rect[i].p[j];
		}

		GN = 2 + 4*RN;
		for (int i = 0; i < GN; i++) {
			G[i][i] = 0;
			for (int j = i+1; j < GN; j++)
				G[i][j] = G[j][i] = visible(V[i], V[j]) ? dist(V[i], V[j]) : 1e99;
		}

		for (int k = 0; k < GN; k++)
			for (int i = 0; i < GN; i++)
				for (int j = 0; j < GN; j++)
					G[i][j] = min(G[i][j], G[i][k] + G[k][j]);

		if (cs != 1) printf("\n");
		printf("Scenario #%d\n", cs);
		printf("   route distance: %.2f\n", G[0][1]);
	}
}
