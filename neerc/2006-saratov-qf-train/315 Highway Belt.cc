#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
using namespace std;

long double EPS = 1e-8;

struct Point {
	long double x, y;
	Point(long double X=0, long double Y=0) : x(X), y(Y) {}

	bool operator ==(const Point &p) const {
		return fabs(p.x - x) < EPS && fabs(p.y - y) < EPS;
	}
};

long double cross(const Point &o, const Point &a, const Point &b) {
	return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}

long double dist(const Point &a, const Point &b) {
	return sqrt(max(0.0L, (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)));
}

struct Road {
	Point A, B;
	bool contains(const Point &p) const {
		if (fabs(cross(p, A, B)) > EPS) return false;
		if (p.x < min(A.x, B.x)-EPS) return false;
		if (p.x > max(A.x, B.x)+EPS) return false;
		if (p.y < min(A.y, B.y)-EPS) return false;
		if (p.y > max(A.y, B.y)+EPS) return false;
		return true;
	}
};

bool intersect(Point &res, const Road &S, const Road &T) {
	long double a1=S.A.y-S.B.y, b1=S.B.x-S.A.x, c1=S.A.y*S.B.x-S.A.x*S.B.y;
	long double a2=T.A.y-T.B.y, b2=T.B.x-T.A.x, c2=T.A.y*T.B.x-T.A.x*T.B.y;

	long double det = a1*b2 - a2*b1;
	if (fabs(det) < EPS) return false;

	res = Point((c1*b2-c2*b1)/det, (a1*c2-a2*c1)/det);
	if ((res == S.A || res == S.B) && (res == T.A || res == T.B))
		return false;
	return S.contains(res) && T.contains(res);
}

vector<Point> V;
int N, start_point;
char got[2][2048], adj[2048][2048];
long double memo[2][2048];

long double f(int first, int x) {
	long double &res = memo[first][x];
	if (got[first][x]) return res;

	got[first][x] = 1;
	res = -1;

	if (!first) {
		if (x == start_point) return res = 0;
		if (fabs(V[x].y) < EPS && V[x].x > 0.0) return res = -1;
	}

	for (int y = 0; y < N; y++) {
		if (adj[x][y] == 0) continue;

		if (!first) {
			if (V[x].y < -EPS && V[y].y > -EPS && y != start_point) continue;
		}

		long double t = f(0, y);
		if (t < -0.5) continue;
		if (t < 0.0) t = 0.0;

		res >?= t + dist(V[x], V[y]);
	}

	return res;
}

void addv(const Point &p) {
	for (int i = 0; i < (int)V.size(); i++)
		if (V[i] == p) return;
	V.push_back(p);
}

int main()
{
	int NR;
	Road R[51];
	cin >> NR;

	Point O(0, 0);

	for (int i = 0; i < NR; i++) {
		cin >> R[i].A.x >> R[i].A.y;
		cin >> R[i].B.x >> R[i].B.y;

		if (fabs(cross(O, R[i].A, R[i].B)) < EPS) { i--; NR--; }
	}

	V.clear();
	for (int i = 0; i < NR; i++) {
		addv(R[i].A);
		addv(R[i].B);
	}

	Road OX;
	OX.A = Point(0, 0);
	OX.B = Point(110, 0);

	for (int i = 0; i < NR; i++) {
		Point X;
		for (int j = i+1; j < NR; j++)
			if (intersect(X, R[i], R[j])) addv(X);
		if (intersect(X, R[i], OX)) addv(X);
	}

	assert(V.size() <= 2048);

	N = V.size();
	memset(adj, 0, sizeof(adj));

	for (int i = 0; i < NR; i++) {
		vector<int> v;
		for (int j = 0; j < N; j++)
			if (R[i].contains(V[j])) v.push_back(j);

		int m = v.size();
		for (int j = 0; j < m; j++) {
			for (int k = j+1; k < m; k++) {
				Point &A = V[v[j]], &B = V[v[k]];
				if (cross(O, A, B) > 0.0)
					adj[v[j]][v[k]] = 1;
				else
					adj[v[k]][v[j]] = 1;
			}
		}
	}

	long double best = -1;
	for (int i = 0; i < N; i++) {
		if (fabs(V[i].y) > EPS || V[i].x < EPS) continue;

		memset(got, 0, sizeof(got));
		start_point = i;
		best >?= f(1, i);
	}

	if (best < EPS)
		printf("0\n");
	else
		printf("%.8lf\n", (double)best);
}
