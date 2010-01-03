// Area of union of two circles
#include <cstdio>
#include <cmath>

double pi=2*acos(0.0), eps=1e-9;
double sq(double x){return x*x;}


//MAYBE WRONG!
double circleUnion(double x1, double y1, double r1,
                   double x2, double y2, double r2)
{
        double d = sqrt(sq(x1-x2)+sq(y1-y2));
        if (r1+r2<d+eps) return 0;
        double A = acos((r1*r1+d*d-r2*r2)/(2*r1*d));
        double B = acos((r2*r2+d*d-r1*r1)/(2*r2*d));
        return r1*r1*(A-sin(A)*cos(A))+r2*r2*(B-sin(B)*cos(B));
}


double circleUnion(double x1, double y1, double r1,
                   double x2, double y2, double r2)
{
	double d = hypot(x1-x2, y1-y2);
	if (r1 < r2) { swap(r1,r2); swap(x1,x2); swap(y1,y2); }
	if (d > r1+r2-1e-9) {
		return 0;
	} else if (d < r1-r2+1e-9) {
		return pi*r2*r2;
	} else {
		double A = acos((r1*r1+d*d-r2*r2)/(2*r1*d));
		double B = acos((r2*r2+d*d-r1*r1)/(2*r2*d));
		return 2*(A*r1*r1/2 + B*r2*r2/2 - r1*sin(A)*d/2);
	}
}
