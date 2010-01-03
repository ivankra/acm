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
#include <map>
using namespace std;

struct Point {
    double x, y;
    Point(){}
    Point(double xx, double yy) : x(xx), y(yy) {}
};

istream &operator >>(istream &is, Point &p) { return is >> p.x >> p.y; }

Point get13(Point A, Point B) { return Point((2*A.x+B.x)/3, (2*A.y+B.y)/3); }

Point isec(Point A, Point B, Point C, Point D)
{
    double a1=A.y-B.y, b1=B.x-A.x, c1=a1*A.x+b1*A.y;
    double a2=C.y-D.y, b2=D.x-C.x, c2=a2*C.x+b2*C.y;

    double det = a1 * b2 - a2 * b1;
    assert(fabs(det) > 1e-9);
    double x = (c1 * b2 - c2 * b1) / det;
    double y = (a1 * c2 - a2 * c1) / det;
    return Point(x, y);
}

int main()
{
    int T;
    cin >> T;

    for (int cs = 1; cs <= T; cs++) {
        Point A, B, C;
        cin >> A >> B >> C;

        Point D = get13(B, C);
        Point E = get13(C, A);
        Point F = get13(A, B);

        Point P = isec(A,D, B,E);
        Point Q = isec(B,E, C,F);
        Point R = isec(C,F, A,D);

        double z = (P.x-R.x)*(Q.y-R.y) - (P.y-R.y)*(Q.x-R.x);
        printf("%.0f\n", fabs(z)/2);
    }
}
