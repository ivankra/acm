#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
using namespace std;
#define foreach(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

double PI = 2*acos(0.0);

struct Line {
	long long a, b, c;
	double x0, y0, dx, dy;
} L[2];  //ax+by=c
int radius;

double sqr(double x) { return x * x; }

vector<double> findAreas()
{
	double ix, iy;
	{
		long long det = L[0].a * L[1].b - L[0].b * L[1].a;
		assert(det != 0);
		ix = (L[0].c * L[1].b - L[0].b * L[1].c) / (double)det;
		iy = (L[0].a * L[1].c - L[0].c * L[1].a) / (double)det;
	}

	vector<double> alphav;
	for (int i = 0; i < 2; i++) {
		for (int sign = -1; sign <= 1; sign += 2) {
			double a = sqr(L[i].dx) + sqr(L[i].dy);
			double b = 2 * L[i].x0 * L[i].dx + 2 * L[i].y0 * L[i].dy;
			double c = sqr(L[i].x0) + sqr(L[i].y0) - radius*radius;

			double det = b*b - 4*a*c;
			assert(det > -0.0001);
			if (det < 1e-9) det = 0;

			double t = (-b + sign * sqrt(det)) / (2 * a);

			double x = L[i].x0 + t * L[i].dx;
			double y = L[i].y0 + t * L[i].dy;
			alphav.push_back(atan2(y, x));
		}
	}

//	printf("ix=%.5f iy=%.5f\n", ix, iy);

	assert(alphav.size() == 4);
	for (int i = 0; i < 4; i++) {
//		printf("  %.5f =>", alphav[i] * 180 / PI);
		while (alphav[i] < 0) alphav[i] += 2*PI;
		while (alphav[i] >= 2*PI) alphav[i] -= 2*PI;
		if (fabs(alphav[i]) < 1e-9 || fabs(alphav[i] - 2*PI) < 1e-9) alphav[i] = 0;
//		printf("%.5f\n", alphav[i] * 180 / PI);
	}
	sort(alphav.begin(), alphav.end());

	vector<double> res;
	for (int i = 0; i < 4; i++) {
		double alpha = alphav[i];
		double beta = alphav[(i + 1) % 4];
		if (beta < alpha) beta += 2*PI;

		double ax = radius * cos(alpha);
		double ay = radius * sin(alpha);

		double bx = radius * cos(beta);
		double by = radius * sin(beta);

		double area = fabs((ax-ix)*(by-iy) - (bx-ix)*(ay-iy)) / 2;
		area += (beta - alpha)/2 * radius*radius;
		area -= fabs(ax*by - bx*ay) / 2;
		res.push_back(area);
	}

	return res;
}

int main()
{
	int h;
	while (scanf("%d %d", &radius, &h) == 2) {
		assert(radius > 0);

		for (int i = 0; i < 2; i++) {
			int x1, y1, x2, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			L[i].a = y2 - y1;
			L[i].b = x1 - x2;
			L[i].c = x1 * L[i].a + y1 * L[i].b;

			L[i].x0 = x1;
			L[i].y0 = y1;
			L[i].dx = x2 - x1;
			L[i].dy = y2 - y1;
			double z = sqrt(sqr(L[i].dx) + sqr(L[i].dy));
			L[i].dx /= z;
			L[i].dy /= z;
		}

		vector<double> a = findAreas();
		sort(a.begin(), a.end());

		for (int i = 0; i < (int)a.size(); i++)
			if (a[i] < 0) a[i] = 0;

		printf("%.2f %.2f\n", a.back()*h, a[0]*h);
	}
}
