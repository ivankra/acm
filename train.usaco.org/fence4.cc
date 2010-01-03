/*
ID: infnty1
PROB: fence4
LANG: C++
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

template<typename T> struct Point {
	T x, y;
	Point(T x=0, T y=0) : x(x), y(y) {}
};
Point<int> F[256], G;
int n;

template<typename T> T cross(Point<T> a, Point<T> b, Point<T> c) {
	return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);	
}

int sgn(int x) { return x<0?-1:(x>0?1:0); }
int sgn(double x) { return (-1e-8<x&&x<1e-8)?0:(x<0?-1:1); }

int visible(int s)
{
	vector<double> u;

	u.push_back(0);
	u.push_back(1);

	for (int i = 0; i < n; i++) {
		/* seg: F[s] + (F[s+1]-F[s]) u
		   F[i].x v + (F[s].x - F[s+1].x) u = F[s].x
		   F[i].y v + (F[s].y - F[s+1].y) u = F[s].y*/
		int d = F[i].x * (F[s].y - F[s+1].y) - F[i].y * (F[s].x - F[s+1].x);
		int t = (F[i].x * F[s].y - F[i].y * F[s].x);
		if (d < 0) { d = -d; t = -t; }
		if (t > 0 && t < d) u.push_back((double)t / (double)d);
	}
	
	sort(u.begin(), u.end());

	for (int i = 0; i < u.size()-1; i++) {
		if (u[i+1] - u[i] < 1e-8) continue;

		double x = F[s].x + (F[s+1].x - F[s].x) * (u[i] + u[i+1])/2.;
		double y = F[s].y + (F[s+1].y - F[s].y) * (u[i] + u[i+1])/2.;
		Point<double> P(x,y), O(0,0);
		int seen = 1;

		for (int j = 0; j < n && seen; j++) {
			if (j == s) continue;
			Point<double> A(F[j].x, F[j].y), B(F[j+1].x, F[j+1].y);
			int d1 = sgn(cross(O, P, A)) * sgn(cross(O, P, B));
			int d2 = sgn(cross(A, B, O)) * sgn(cross(A, B, P));
			if (d1 <= 0 && d2 <= 0) seen = 0;
		}

		if (seen) return 1;
	}

	return 0;
}

bool on(Point<int> P, Point<int> A, Point<int> B) {
	return (A.x <? B.x) <= P.x && P.x <= (A.x >? B.x) &&
	       (A.y <? B.y) <= P.y && P.y <= (A.y >? B.y) &&
	       ((P.x - A.x) * (B.y - A.y) - (P.y - A.y) * (B.x - A.x)) == 0;
}

int valid()
{
	if (n < 3)
		return 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++)
			if (F[i].x == F[j].x && F[i].y == F[j].y) return 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) continue;

			if (on(F[i], F[j], F[j+1]) && on(F[i+1], F[j], F[j+1])) return 0;
			if (on(F[j], F[i], F[i+1]) && on(F[j+1], F[i], F[i+1])) return 0;

			int d1 = sgn(cross(F[i],F[i+1],F[j]))*sgn(cross(F[i],F[i+1],F[j+1]));
			int d2 = sgn(cross(F[j],F[j+1],F[i]))*sgn(cross(F[j],F[j+1],F[i+1]));
			if (d1 < 0 && d2 < 0) return 0;
		}
	}
	
	return 1;
}

void check(int s, vector<string> &out)
{
	if (visible(s)) {
		int a = s, b = (s + 1) % n;
		char buf[256];
		if (a > b) swap(a, b);
		sprintf(buf, "%d %d %d %d",
			F[a].x+G.x, F[a].y+G.y, F[b].x+G.x, F[b].y+G.y);
		out.push_back(string(buf));
	}
}

int main()
{
	freopen("fence4.in", "r", stdin);
	freopen("fence4.out", "w", stdout);

	scanf("%d %d %d", &n, &G.x, &G.y);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &F[i].x, &F[i].y);
		F[i].x -= G.x;
		F[i].y -= G.y;
	}
	F[n] = F[0];

	if (!valid()) {
		printf("NOFENCE\n");
	} else {
		vector<string> s;
		for (int i = 0; i < n-2; i++) check(i, s);
		check(n-1, s);
		check(n-2, s);
		printf("%d\n", s.size());
		for (int i = 0; i < (int)s.size(); i++) printf("%s\n", s[i].c_str());
	}

	return 0;
}
