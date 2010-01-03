#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int main()
{
	double x1, y1, x2, y2, r1, r2, pi=2*acos(0.0);
	scanf("%lf %lf %lf %lf %lf %lf",&x1,&y1,&r1,&x2,&y2,&r2); r1/=2; r2/=2;
	double d = hypot(x1-x2, y1-y2);
	if (r1 < r2) { swap(r1,r2); swap(x1,x2); swap(y1,y2); }
	if (d > r1+r2-1e-9) {
		printf("0.000\n");
	} else if (d < r1-r2+1e-9) {
		printf("%.3f\n", pi*r2*r2);
	} else {
		double A = acos((r1*r1+d*d-r2*r2)/(2*r1*d));
		double B = acos((r2*r2+d*d-r1*r1)/(2*r2*d));
		printf("%.3f\n", 2*(A*r1*r1/2 + B*r2*r2/2 - r1*sin(A)*d/2));
	}
}
