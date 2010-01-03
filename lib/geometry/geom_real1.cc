#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>
#define EPS 1e-12
using namespace std;

double PI = 2*acos(0.);

struct Point {
        double x, y, z;
        Point(double x=0, double y=0, double z=0) : x(x), y(y), z(z) {}
        Point operator +(const Point &b) const { return Point(x+b.x,y+b.y,z+b.z); }
        Point operator -(const Point &b) const { return Point(x-b.x,y-b.y,z-b.z); }
        Point operator *(double c) { return Point(x*c, y*c, z*c); }
        double operator *(const Point &b) const { return x*b.x+y*b.y+z*b.z; }
        Point operator ^(const Point &b) const { return Point(y*b.z-z*b.y, z*b.x-x*b.z, x*b.y-y*b.x); }
        double sq() const { return x*x+y*y+z*z; }
        double abs() const { return sqrt(sq()); }
};

Point operator *(double c, const Point &p) { return Point(c*p.x, c*p.y, c*p.z); }
double dot(Point a, Point b) { return a.x*b.x+a.y*b.y+a.z*b.z; }
Point cross(Point a, Point b) { return Point(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x); }
double abs(Point a) { return a.abs(); }
double dist(const Point &A, const Point &B) { return abs(A-B); }
double angle(const Point &A, const Point &B, const Point &C) { return ((A-B)*(C-B))/(abs(A-B)*abs(C-B)); }
Point polar(double r, double a) { return Point(r*sin(a), r*cos(a)); };
Point polar(double a) { return Point(sin(a), cos(a)); }

/* Heron's formula: area of a triangle from length of its sides. */
double heron(double a, double b, double c) {
        if (a+b<c+EPS || b+c<a+EPS || a+c<b+EPS) return 0;
        double p = (a+b+c)/2.0;
        return sqrt((p*(p-a)*(p-b)*(p-c)) >? 0.);
}

/*
 *  Computes the distance between two points on a sphere along great circle.
 *
 *  (p1,t1), (p2,t2) -- latitude (in [-pi/2, pi/2]) and longitute of points.
 *  r = radius of the sphere  (Earth's radius is approximately 6378 km.)
 */
double gcdist_1(double p1, double t1, double p2, double t2, double r=1.) {
        double a = cos(p1) * cos(p2) * cos(t1 - t2) + sin(p1) * sin(p2);
        return acos((a >? -1.) <? 1.) * r;
}
