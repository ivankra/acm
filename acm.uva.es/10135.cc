#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

const double EPS = 1e-8;
double PI = 2*acos(0.0);

struct Point {
	double x, y, ang;
	bool operator <(const Point &p) const {
		if (fabs(ang - p.ang) < EPS || fabs(ang - p.ang - 2*PI) < EPS)
			return x*x+y*y < p.x*p.x+p.y*p.y;
		return ang < p.ang;
	}
};

bool lex(const Point &a, const Point &b) {
	if (fabs(a.x - b.x) > EPS) return a.x < b.x;
	return a.y < b.y;
}

double cross(const Point &o, const Point &a, const Point &b) {
	return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}

double dist(const Point &a, const Point &b) {
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

int N;
Point P[1024];

double solve() {
	for (int i = 0; i < N; i++)
		P[i].ang = atan2(P[i].y, P[i].x);
	sort(P, P+N);

	Point O = { 0, 0, 0 };

	double best = 1e99;
	for (int s = 0; s < N; s++) {
		vector<Point> h;
		h.push_back(O);
		h.push_back(P[s]);

		for (int t = (s+1)%N; t != s; t = (t + 1) % N) {
			while (h.size() >= 2 && cross(h[h.size()-2], h.back(), P[t]) < EPS)
				h.pop_back();
			h.push_back(P[t]);
		}

		h.push_back(O);

		double res = 2;
		for (int i = 1; i < (int)h.size(); i++)
			res += dist(h[i-1], h[i]);
		best = min(best, res);
	}

	P[N++] = O;
	sort(P, P+N, lex);

	double res = 2;
	for (int k = 0; k < 2; k++) {
		vector<Point> h;
		for (int i = 0; i < N; i++) {
			Point p = P[k==0 ? i : (N-1-i)];
			while (h.size() >= 2 && cross(h[h.size()-2], h.back(), p) < EPS)
				h.pop_back();
			h.push_back(p);
		}

		for (int i = 1; i < (int)h.size(); i++)
			res += dist(h[i-1], h[i]);
	}
	best = max(best, res);

	return best;
}

int main() {
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%lf %lf", &P[i].x, &P[i].y);
			if (fabs(P[i].x) < EPS && fabs(P[i].y) < EPS) { i--; N--; }
		}

		if (cs > 1) printf("\n");
		printf("%.2f\n", solve());
	}
}
