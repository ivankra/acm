#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

int n;

double sol()
{
	double x[4], y[4];
	for (int i = 1; i <= 3; i++) scanf("%lf %lf", &x[i], &y[i]);

	double a1 = 2*x[2]-2*x[1], b1 = 2*y[2]-2*y[1], c1=x[2]*x[2]+y[2]*y[2]-x[1]*x[1]-y[1]*y[1];
	double a2 = 2*x[3]-2*x[1], b2 = 2*y[3]-2*y[1], c2=x[3]*x[3]+y[3]*y[3]-x[1]*x[1]-y[1]*y[1];
	double d = a1*b2-b1*a2;

	double x0 = (c1*b2 - b1*c2) / d;
	double y0 = (a1*c2 - c1*a2) / d;
	double r = sqrt((x[1]-x0)*(x[1]-x0) + (y[1]-y0)*(y[1]-y0));

	double a = atan2(y[1]-y0, x[1]-x0);
	d = 4.*acos(0.) / n;
	double xmin, xmax, ymin, ymax;

	for (int i = 0; i < n; i++, a += d) {
		double X=r*cos(a), Y=r*sin(a);
		if (i == 0) { xmin=xmax=X; ymin=ymax=Y; continue; }
		xmin = min(xmin,X); xmax = max(xmax,X);
		ymin = min(ymin,Y); ymax = max(ymax,Y);
	}		

	return (xmax-xmin)*(ymax-ymin);
}

int main()
{
	int t;
	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++)
		printf("Polygon %d: %.3f\n", t, sol()+1e-12);
	return 0;
}
