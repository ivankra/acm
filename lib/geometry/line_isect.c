/* Line intersections in 2D */
#include <cmath>
#define EPS 1e-12

struct pt { double x,y; };

pt isect(pt a, pt b, pt c, pt d) {
	double a1=a.y-b.y, b1=b.x-a.x, c1=a1*a.x+b1*a.y;
	double a2=c.y-d.y, b2=d.x-c.x, c2=a2*c.x+b2*c.y;
	double D=a1*b2-a2*b1;
	pt p={(c1*b2-c2*b1)/D,(a1*c2-a2*c1)/D};
	return p;
}

/* Returns: 0=no intersection, 1=one point of intersection, 2=lines are same */
int isect(pt *r, pt a, pt b, pt c, pt d) {
	double a1=a.y-b.y, b1=b.x-a.x, c1=a1*a.x+b1*a.y;
	double a2=c.y-d.y, b2=d.x-c.x, c2=a2*c.x+b2*c.y;
	double D=a1*b2-a2*b1;
	if (fabs(D) < EPS) return fabs(a2*a.x+b2*a.y-c2)<EPS ? 2 : 0;
	if (r != NULL) { r->x = (c1*b2-c2*b1)/D; r->y = (a1*c2-a2*c1)/D; }
	return 1;
}
