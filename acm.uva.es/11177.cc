#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

double EPS = 1e-6, PI = 2*acos(0.0);

struct Point {
	double x, y;
	Point(double X=0, double Y=0) : x(X), y(Y) { }
	Point operator -(const Point &p) const { return Point(x-p.x, y-p.y); }
};

double cross(const Point &a, const Point &b) { return a.x*b.y - a.y*b.x; }
double dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }

double angle(const Point &a, const Point &b) {
	double cs = dot(a, b) / sqrt(dot(a, a)) / sqrt(dot(b, b));
	cs >?= -1.0;
	cs <?= 1.0;
	return acos(cs);
}

double areaOfIntersection(double R, Point P[], int N) {
	double answer = 0;
	for (int i = 0; i < N; i++) {
		Point A = P[i];
		Point B = P[(i+1)%N];
		if (cross(A, B) < 0) swap(A, B);

		double a = dot(B-A, B-A), b = 2*dot(A,B-A), c = dot(A,A)-R*R;
		if (fabs(a) < EPS) continue;

		double v[10];
		int K = 0;
		v[K++] = 0;
		v[K++] = 1;

		double det = b*b - 4*a*c;
		if (det > EPS) {
			for (int sign = -1; sign <= 1; sign += 2) {
				double t = (-b + sign * sqrt(det)) / (2 * a);
				if (EPS < t && t < 1-EPS)
					v[K++] = t;
			}
		}

		sort(v, v+K);

		Point Q[10];
		for (int i = 0; i < K; i++) {
			Q[i].x = A.x + v[i] * (B.x - A.x);
			Q[i].y = A.y + v[i] * (B.y - A.y);
		}

		for (int i = 0; i < K-1; i++) {
			if (dot(Q[i], Q[i]) < R*R+EPS && dot(Q[i+1], Q[i+1]) < R*R+EPS) {
				answer += 0.5*fabs(cross(Q[i], Q[i+1]));
			} else {
				answer += 0.5*R*R*angle(Q[i], Q[i+1]);
			}
		}
	}
//printf("areaOfIntersection(R=%.5f) = %.5f\n",R,answer);
	return answer;
}

int main() {
	double minArea;
	Point P[64];
	int N;

	for (int cs = 1; scanf("%d %lf", &N, &minArea) == 2 && N > 0; cs++) {
		for (int i = 0; i < N; i++)
			scanf("%lf %lf", &P[i].x, &P[i].y);
		P[N] = P[0];

		double area = 0;
		for (int i = 0; i < N; i++)
			area += cross(P[i], P[i+1]);
		area = fabs(area/2.0);

		double left = sqrt(max(0.0, minArea/PI));
		double right = 0;
		for (int i = 0; i < N; i++)
			right >?= max(fabs(P[i].x), fabs(P[i].y));
//printf("left=%.5f right=%.5f  area=%.5f  minArea=%.5f\n",left,right,area,minArea);
		while (right - left > 1e-6) {
			double mid = (left + right) / 2;
			if (areaOfIntersection(mid, P, N) < minArea)
				left = mid;
			else
				right = mid;
		}
		printf("Case %d: %.2f\n", cs, left);
	}
}
