#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;
typedef long long int64;

struct Point {
	double x, y;
	Point(double X=0, double Y=0) : x(X), y(Y) {}

	vector<string> str() {
		char s[100];
		sprintf(s, "%.3f", x);
		vector<string> res;
		res.push_back(s);
		sprintf(s, "%.3f", y);
		res.push_back(s);
		return res;
	}
};

double dot(const Point &a, const Point &b) { return a.x*b.x + a.y*b.y; }
double abs(const Point &p) { return sqrt(max(0.0, dot(p, p))); }
Point operator +(const Point &a, const Point &b) { return Point(a.x+b.x, a.y+b.y); }
Point operator -(const Point &a, const Point &b) { return Point(a.x-b.x, a.y-b.y); }
Point polar(double r, double a) { return Point(r*cos(a), r*sin(a)); }

struct LuckyBottle {
	vector<Point> reduce(const vector<Point> &p) {
		vector<Point> q;

		for (int i = 0; i+1 < (int)p.size(); i++) {
			Point A = p[i], B = p[i+1];
			Point M((A.x+B.x)/2, (A.y+B.y)/2);

			double ca = abs(A-M) / 2.0;
			double delta = acos((ca >? -1.0) <? 1.0);
			double ang = atan2(B.y-A.y, B.x-A.x);

			Point C1 = A + polar(2, ang+delta);
			Point C2 = A + polar(2, ang-delta);
			q.push_back(C1.y > C2.y ? C1 : C2);
		}

		return q;
	}

	vector<string> getLuckyBottle(vector<string> lowbottle, int row, int index) {
		int N = lowbottle.size();

		vector<Point> p(N);
		for (int i = 0; i < N; i++) {
			p[i].y = 1;
			sscanf(lowbottle[i].c_str(), "%lf", &p[i].x);
		}

		for (int r = 1; r <= row-1; r++)
			p = reduce(p);
		return p[index-1].str();
	}
};
