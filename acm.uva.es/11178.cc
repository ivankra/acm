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
};

void read(Point &p) { scanf("%lf %lf", &p.x, &p.y); }

double dist(const Point &A, const Point &B) {
	double dx = A.x - B.x;
	double dy = A.y - B.y;
	return sqrt(max(0.0, dx*dx+dy*dy));
}

double angle(const Point &A, const Point &B, const Point &C) {
	double t = (C.x-B.x)*(A.x-B.x) + (C.y-B.y)*(A.y-B.y);
	t /= dist(A, B);
	t /= dist(B, C);
	t <?= 1.0;
	t >?= -1.0;
	return acos(t);
}

double PI = 2*acos(0.0);

Point morley(const Point &A, const Point &B, double alpha, double beta) {
	double gamma = PI - alpha - beta;
	double AF = dist(A, B) * sin(beta) / sin(gamma);

	double theta = atan2(B.y-A.y, B.x-A.x) + alpha;
	Point F(A.x + AF * cos(theta), A.y + AF * sin(theta));
	return F;
}

int main() {
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		Point A, B, C;
		read(A); read(B); read(C);

		double BAC = angle(B, A, C);
		double ABC = angle(A, B, C);
		double BCA = angle(B, C, A);

		Point F = morley(A, B, BAC/3, ABC/3);
		Point D = morley(B, C, ABC/3, BCA/3);
		Point E = morley(C, A, BCA/3, BAC/3);

		printf("%.6f %.6f ", D.x, D.y);
		printf("%.6f %.6f ", E.x, E.y);
		printf("%.6f %.6f\n", F.x, F.y);
	}
}
