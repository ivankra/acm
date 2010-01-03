#include <cstdio>
#include <cmath>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>
#define EPS 1e-9
using namespace std;

struct Point {
	double x, y;
	Point(double x=0, double y=0) : x(x), y(y) {}
};

bool operator <(const Point &a, const Point &b)
{
	return a.x<b.x-EPS || (a.x<b.x+EPS && a.y<b.y-EPS);
};

bool operator ==(const Point &a, const Point &b)
{
	return fabs(a.x-b.x)<EPS && fabs(a.y-b.y)<EPS;
};

struct Segment {
	double a, b, c;
	Point A, B;

	Segment(Point p1, Point p2) {
		A = p1; B = p2;
		c=(a=B.y-A.y)*A.x+(b=A.x-B.x)*A.y;
	}
};

int onseg(Point r, Segment s)
{
	if (fabs(s.a*r.x+s.b*r.y-s.c) > EPS) return 0;
	return (s.A.x <? s.B.x) - EPS < r.x && r.x < (s.A.x >? s.B.x) + EPS &&
	       (s.A.y <? s.B.y) - EPS < r.y && r.y < (s.A.y >? s.B.y) + EPS;
}

int isect(Point &r, Segment &s, Segment &t)
{
	double d = s.a * t.b - s.b * t.a;
	if (fabs(d) < EPS) return 0;
	r = Point((s.c * t.b - s.b * t.c) / d, (s.a * t.c - s.c * t.a) / d);
	return onseg(r, s) && onseg(r, t);
}

int overlap(Segment &s, Segment &t)
{
	if (fabs(s.a * t.b - s.b * t.a) > EPS) return 0;
	if (onseg(t.A, s) && onseg(t.B, s)) return 1;
	if (onseg(s.A, t) && onseg(s.B, t)) { s = t; return 1; }
	if (onseg(s.B, t)) swap(s.A, s.B);
	if (!onseg(s.A, t)) return 0;
	if (onseg(t.B, s)) swap(t.A, t.B);
	if (!onseg(t.A, s)) return 0;
	s = Segment(s.B, t.B);
	return 1;
}

vector<Segment> S;
vector<Point> V;
int adj[128][128];

int main()
{
	int i, j, k, n, r;

	while (scanf("%d", &n) == 1) {
		S.clear();
		for (i = 0; i < n; i++) {
			double x1, y1, x2, y2;
			scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
			S.push_back(Segment(Point(x1,y1), Point(x2,y2)));
		}

		do {
			for (i = k = 0; i < n; i++)
				for (j = i+1; j < n; j++)
					if (overlap(S[i], S[j])) {
						S.erase(S.begin()+j); n--; k++;
						break;
					}
		} while (k);

		V.clear();
		for (i = 0; i < n; i++) {
			V.push_back(S[i].A);
			V.push_back(S[i].B);
			for (j = 0; j < i; j++) {
				Point r;
				if (isect(r, S[i], S[j])) V.push_back(r);
			}
		}
		sort(V.begin(), V.end());
		V.erase(unique(V.begin(), V.end()), V.end());

		r = 0;
		memset(adj, 0, sizeof(adj));
		for (i = 0; i < n; i++) {
			vector<int> P;
			P.clear();
			for (j = 0; j < V.size(); j++)
				if (onseg(V[j], S[i])) P.push_back(j);

			k = P.size();
			r -= k*(k-1)*(k-2)/6;

			for (j = 0; j < P.size(); j++)
				for (k = 0; k < P.size(); k++)
					adj[P[j]][P[k]] = 1;
		}

		n = V.size();
		for (i = 0; i < n; i++)
			for (j = i+1; j < n; j++) {
				if (!adj[i][j]) continue;
				for (k = j+1; k < n; k++)
					r += adj[j][k] & adj[i][k];
			}

		printf("%d\n", r);
	}

	return 0;
}
