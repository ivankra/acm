#include <cstdio>
#include <cmath>

template<typename T> struct Point {
	T x, y, z;
	Point(T x=0, T y=0, T z=0) : x(x), y(y), z(z) {}
	template<typename Q> Point(Point<Q> p) : x(p.x), y(p.y), z(p.z) {}
	Point operator +(const Point &b) const { return Point(x+b.x,y+b.y,z+b.z); }
	Point operator -(const Point &b) const { return Point(x-b.x,y-b.y,z-b.z); }
	Point operator *(T c) { return Point(x*c, y*c, z*c); }
/*dot*/	T operator *(const Point &b) const { return x*b.x+y*b.y+z*b.z; }
/* x */	Point operator ^(const Point &b) const { return Point(y*b.z-z*b.y, z*b.x-x*b.z, x*b.y-y*b.x); }
	T sq() const { return x*x+y*y+z*z; }
	double abs() const { return sqrt((double)sq()); }
};

template<typename T> Point<T> operator *(T c, const Point<T> &p) { return Point<T>(c*p.x, c*p.y, c*p.z); }
template<typename T> T dot(Point<T> a, Point<T> b) { return a.x*b.x+a.y*b.y+a.z*b.z; }
template<typename T> Point<T> cross(Point<T> a, Point<T> b) { return Point<T>(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x); }

typedef Point<double> dPoint;

typedef long long i64;
typedef Point<i64> iPoint;

double abs(dPoint a) { return sqrt(a*a >? 0.); }
double dist(const dPoint &A, const dPoint &B) { return abs(A-B); }
double angle(const dPoint &A, const dPoint &B, const dPoint &C) { return ((A-B)*(C-B))/(abs(A-B)*abs(C-B)); }
dPoint polar(double r, double a) { return dPoint(r*sin(a), r*cos(a)); };
dPoint polar(double a) { return dPoint(sin(a), cos(a)); }



int main() {
	dPoint p(1,2,3), q(2,4,6);

	printf("p = (%.1f, %.1f, %.1f)\n", p.x, p.y, p.z);
	printf("q = (%.1f, %.1f, %.1f)\n", q.x, q.y, q.z);

	dPoint r = p ^ q;
	printf("pxq = (%.1f, %.1f, %.1f)\n", r.x, r.y, r.z);

	return 0;
}
