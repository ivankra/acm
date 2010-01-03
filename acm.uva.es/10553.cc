#include <cstdio>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

struct Point {
	double x, y;
	Point(double x=0, double y=0) : x(x), y(y) {}
} X;

Point operator +(const Point &a, const Point &b){return Point(a.x+b.x,a.y+b.y);}
Point operator -(const Point &a, const Point &b){return Point(a.x-b.x,a.y-b.y);}

double dot(Point a, Point b) { return a.x*b.x+a.y*b.y; }
double cross(Point a, Point b) { return a.x*b.y-a.y*b.x; }
double len(Point a) { return sqrt(dot(a,a)); }

Point rad(double r, double a) { return Point(r*cos(a), r*sin(a)); }

int main()
{
	string dirs[] = {
		"N","NbE","NNE","NEbN","NE","NEbE","ENE","EbN","E","EbS","ESE",
		"SEbE","SE","SEbS","SSE","SbE","S","SbW","SSW","SWbS","SW",
		"SWbW","WSW","WbS","W","WbN","WNW","NWbW","NW","NWbN","NNW",
		"NbW"
	};
	double pi = 2*acos(0.), wr[1024], wa[1024], d;
	char s[128];
	int n;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (int i = 0; i < n; i++) {
			scanf(" %s %lf", s, &wr[i]);
			wa[i] = (find(dirs, dirs+32, s) - dirs) * pi / 16.;
		}

		scanf("%lf", &d);
		d *= pi / 180.;

		X = Point(0,0);
		for (int i = 0; i < n; i++)
			X = X + rad(wr[i], wa[i]+d);

		d = len(X);
		Point A(0,0);
		for (int i = 0; i < n; i++) {
			Point B = A + rad(wr[i], wa[i]);
			d <?= len(A-X) <? len(B-X);
			if (dot(X-A,B-A)>0 && dot(X-B,A-B)>0 && len(A-B)>1e-8)
				d <?= fabs(cross(A-X,B-X)) / len(A-B);
			A = B;
		}

		printf("%.2f\n", d);
	}

	return 0;
}
