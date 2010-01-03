#include <stdio.h>
#include <math.h>
using namespace std;
struct pt { double x,y; };
struct line { double a,b,c; };

double pi;

line through(pt P, pt Q) { line l={P.y-Q.y,Q.x-P.x,0};l.c=P.x*l.a+P.y*l.b;return l;}

pt isect(line l, line m) {
	double d = l.a*m.b-m.a*l.b;
	pt I={(l.c*m.b-m.c*l.b)/d,(l.a*m.c-m.a*l.c)/d};
	return I;
}

double area(int n) { return n*sin(2*pi/n)/2; }

double f(int n, int k)
{
	double t=2*pi/n;
	
	if (k <= 1) return area(n);
	if (k >= n/2) return 0.;

	pt A={1,0}, B={cos(k*t),sin(k*t)}, C={cos(t),sin(t)}, D={cos(k*t+t),sin(k*t+t)};
	line l1=through(A,B), l2=through(C,D);
	pt P=isect(l1,l2);
	return (P.x*P.x+P.y*P.y)*area(n);
}

double sol(int n, int k)
{
	if (k > n/2 || k<1) return 0;
	k = n/2 - k;
	if (k == 0) return pi-area(n);
	return f(n,k)-f(n,k+1);
}

int main()
{
	int t, n, k;
	double r;
	pi = 2. * acos(0.);
	for (scanf("%d", &t); t-- > 0 && scanf("%lf %d %d", &r, &n, &k) == 3;)
		printf("%.4f\n", r*r*sol(n,k));
	return 0;
}

