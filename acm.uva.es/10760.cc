#include <stdio.h>
#include <assert.h>
#include <math.h>
#define EPS 1e-8

struct vec { double x, y; };
struct seg { vec a, b, d; };

int zero(double x) { return fabs(x)<EPS; }
int zero(vec v) { return zero(v.x) && zero(v.y); }
int zero(seg s) { return zero(s.a) && zero(s.b); }
double operator *(vec &a, vec &b) { return a.x*b.x+a.y*b.y; }
double skew(vec a, vec b) { return a.x*b.y-a.y*b.x; }
vec operator -(vec &a, vec &b) { vec c={a.x-b.x,a.y-b.y}; return c;}
double sq(double x) { return x*x; }
double norm(vec v) { return sqrt(v*v); }

int main()
{
	seg s1, s2;
	double pi=2.*acos(0.);

	for (;;) {
		int i = scanf("%lf%lf%lf%lf%lf%lf%lf%lf",
			      &s1.a.x, &s1.a.y, &s2.a.x, &s2.a.y,
			      &s1.b.x, &s1.b.y, &s2.b.x, &s2.b.y);
		if (i < 8 || (zero(s1) && zero(s2))) break;

		s1.d = s1.b - s1.a;
		s2.d = s2.b - s2.a;

		if (zero(s1.a-s2.a) && zero(s1.b-s2.b)) { printf("No move.\n"); continue; }

		if (zero(s1.d - s2.d)) {
			printf("Translation by vector <%.1f,%.1f>.\n",
				s2.a.x-s1.a.x+EPS, s2.a.y-s1.a.y+EPS);
			continue;
		}

		double a1=2*s2.a.x-2*s1.a.x, b1=2*s2.a.y-2*s1.a.y;
		double c1=sq(s2.a.x)-sq(s1.a.x)+sq(s2.a.y)-sq(s1.a.y);

		double a2=2*s2.b.x-2*s1.b.x, b2=2*s2.b.y-2*s1.b.y;
		double c2=sq(s2.b.x)-sq(s1.b.x)+sq(s2.b.y)-sq(s1.b.y);

		double d = a1*b2-a2*b1;

		if (zero(d)) {
			a2 = s1.a.y-s1.b.y;
			b2 = s1.b.x-s1.a.x;
			c2 = s1.a.x*a2+s1.a.y*b2;
			d = a1*b2-a2*b1;
		}

		vec O={(c1*b2-b1*c2)/d,(a1*c2-c1*a2)/d};
		vec U = s1.a-O, V=s2.a-O;
		double t = U*V/(norm(U)*norm(V));
		t = acos(t)*180/pi;
		if (skew(U, V) < 0.) t=-t;
		while (t < -EPS) t += 360;
		while (t > 360-EPS) t -= 360;
		if (zero(t)) t = EPS;

		printf("Rotation around (%.1f,%.1f) by %.1f degrees counterclockwise.\n", O.x+EPS, O.y+EPS, t);
	}

	return 0;
}
