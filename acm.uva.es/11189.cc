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
	double x, y;
	Point(double x=0, double y=0) : x(x), y(y) { }
	Point operator +(const Point &p) const { return Point(x+p.x, y+p.y); }
	Point operator -(const Point &p) const { return Point(x-p.x, y-p.y); }
};

double dot(const Point &A, const Point &B) { return A.x * B.x + A.y * B.y; }

double PI = 2 * acos(0.0), R;
Point P[10];

int solve() {
	double EPS = 1e-9;
	if (R < EPS) return 0;

	double area = 0;
	for (int i = 0; i < 4; i++)
		area += P[i].x * P[(i+1)%4].y - P[(i+1)%4].x * P[i].y;

	if (area < 0) { area = -area; reverse(P, P+4); }
	area /= 2;

	Point O;
	P[4] = P[0];
	for (int i = 0; i < 4; i++) {
		O.x += (P[i].x + P[i+1].x)/3 * (P[i].x * P[i+1].y - P[i+1].x * P[i].y)/2;
		O.y += (P[i].y + P[i+1].y)/3 * (P[i].x * P[i+1].y - P[i+1].x * P[i].y)/2;
	}
	O.x /= area; O.y /= area;

	for (int i = 0; i < 4; i++) {
		P[i].x -= O.x;
		P[i].y -= O.y;
		P[4+i] = P[i];
	}

	//printf("O=(%.5f, %.5f)  R=%.5f  area=%.5f\n", O.x, O.y, R, area);

	vector<Point> isec;
	for (int i = 0; i < 4; i++) {
		double d = sqrt(dot(P[i], P[i]));
		if (fabs(d - R) < EPS)
			isec.push_back(P[i]);
	}

	for (int i = 0; i < 4; i++) {
		Point A = P[i], B = P[i+1];

		double a = dot(B-A, B-A), b = 2*dot(B-A,A), c = dot(A,A)-R*R;
		if (fabs(a) < EPS) continue;

		double det = b*b-4*a*c;
		if (det < -EPS) continue;

		if (det < 1e-9) det = 0;

		for (int sign = -1; sign <= 1; sign += 2) {
			double t = (-b + sign*sqrt(det)) / (2*a);
			if (t < EPS || t > 1-EPS) continue;

			Point p;
			p.x = A.x + t * (B.x - A.x);
			p.y = A.y + t * (B.y - A.y);
			isec.push_back(p);
		}
	}

	int res = 0;
	for (int i = 0; i < (int)isec.size(); i++) {
		for (int j = 0; ; j++) {
			if (j == i) { res++; break; }

			if (fabs(isec[i].x - isec[j].x) < EPS && fabs(isec[i].y - isec[j].y) < EPS)
				break;
		}
	}

	return res;
}

int main() {
	double len, T;
	for (int cs = 1; scanf("%lf %lf", &len, &T) == 2 && len > 0.01; cs++) {
		for (int i = 0; i < 4; i++)
			scanf("%lf %lf", &P[i].x, &P[i].y);

		R = T*T/(4*PI*PI)*981 - len;

		int res = solve();
		printf("Pendulum %d: ", cs);
		if (res <= 0)
			printf("No\n");
		else
			printf("Yes %d\n", res);
	}
}
