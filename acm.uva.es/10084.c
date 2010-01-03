#include <stdio.h>
#include <math.h>
#define EPS 1e-9

typedef struct { double x,y; } pt;
double c1, c2, c3;

int isect(pt a, pt b, pt *z)
{
	double d1=b.y-a.y, d2=a.x-b.x, d3=a.x*d1+a.y*d2, t=c1*d2-c2*d1;

	if (fabs(t) < EPS) return 0;
	z->x = (c3 * d2 - c2 * d3) / t;
	z->y = (c1 * d3 - c3 * d1) / t;

	if (fabs(z->x-a.x)<EPS && fabs(z->y-a.y)<EPS) return 0;
	if (fabs(z->x-b.x)<EPS && fabs(z->y-b.y)<EPS) return 0;

	if (z->x < a.x-EPS && z->x < b.x-EPS) return 0;
	if (z->x > a.x+EPS && z->x > b.x+EPS) return 0;
	if (z->y < a.y-EPS && z->y < b.y-EPS) return 0;
	if (z->y > a.y+EPS && z->y > b.y+EPS) return 0;

	return 1;
}

int main()
{
	pt r[4096]={{0,0},{10,0},{10,10},{0,10},{0,0}}, q[4096], a={0,0}, b;
	double m=100.;
	int i, rn=4, qn;
	char s[128];

	for (; scanf("%lf %lf %s", &b.x, &b.y, s) == 3; a = b) {
		if (s[0] == 'S' || s[0] == 's') {
			if (fabs(a.x-b.x)<EPS && fabs(a.y-b.y)<EPS)
				printf("%.2f\n", m);
			else {
				rn = 0; m = 0.;
				printf("0.00\n");
			}
			continue;
		}

		c1 = 2*a.x-2*b.x;
		c2 = 2*a.y-2*b.y;
		c3 = a.x*a.x-b.x*b.x+a.y*a.y-b.y*b.y;
		if (s[0] == 'H' || s[0] == 'h') { c1=-c1; c2=-c2; c3=-c3; }

		r[rn] = r[0];
		for (qn = i = 0; i < rn; i++) {
			q[qn++] = r[i];
			if (isect(r[i], r[i+1], &q[qn])) qn++;
		}

		for (rn = i = 0; i < qn; i++)
			if (c1*q[i].x+c2*q[i].y > c3-EPS) r[rn++] = q[i];
		r[rn] = r[0];

		for (m = 0, i = 0; i < rn; i++)
			m += r[i].x*r[i+1].y-r[i+1].x*r[i].y;
		m = fabs(m)/2+1e-12;
		printf("%.2f\n", m);
	}

	return 0;
}
