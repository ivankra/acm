#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define EPS 1e-9

struct Point {
        double x, y;
        Point(double x=0, double y=0) : x(x), y(y) {}
};

Point operator -(const Point &p, const Point &q) { return Point(p.x-q.x,p.y-q.y); }
double dot(const Point &p, const Point &q) { return p.x*q.x+p.y*q.y; }
double abs(const Point &p) { return sqrt(dot(p,p)); }

double fix(Point C, double R, Point S, Point T) {
        double a = dot(T-S,T-S), b = 2*dot(T-S,S-C), c = dot(S-C,S-C)-R*R;
        double d = b*b-4*a*c;
        if (d < EPS || a < EPS) return 0;
        d = sqrt(d);

        double t1 = (-b-d)/(2*a), t2 = (-b+d)/(2*a);
        if (t1 > t2) swap(t1, t2);
        if (t2 < EPS || t1 > 1.-EPS || t2-t1 < EPS) return 0;

        double w = dot(S-C,S-C) + (t1+t2)*dot(T-S,S-C) + t1*t2*dot(T-S,T-S);
        w /= R*R;
        if (w < -1+EPS) w = -1;
        if (w > 1-EPS) w = 1;
        return acos(w)*R-(t2-t1)*abs(T-S);
}

int main()
{
        Point C[128], S, T;
        double R[128];
        int N;

        scanf("%d", &N);
        for (int i = 0; i < N; i++)
                scanf("%lf %lf %lf", &C[i].x, &C[i].y, &R[i]);
        scanf("%lf %lf %lf %lf", &S.x, &S.y, &T.x, &T.y);

        double ret = abs(T-S);
        for (int i = 0; i < N; i++)
                ret += fix(C[i], R[i], S, T);
        printf("%.3f\n", ret);
        return 0;
}
