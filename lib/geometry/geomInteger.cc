#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long LL;

struct Point {
	LL x, y;
	Point() {}
	Point(LL x_, LL y_) : x(x_), y(y_) {}
};

Point operator +(const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator -(const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator *(LL c, const Point &p) { return Point(c * p.x, c * p.y); }
Point operator ==(const Point &a, const Point &b)  { return a.x == b.x && a.y == b.y; }
Point operator <(const Point &a, const Point &b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }

LL dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
LL cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
LL cross(const Point &o, const Point &a, const Point &b) { return cross(a-o, b-o); }

int sign(LL x) { return x == 0 ? 0 : (x > 0 ? 1 : -1); }
