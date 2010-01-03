#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

#if 0
int n=12;
char *colors[] = {   /* colors for regions, starting from outermost */
	"1 0 0",
	"0.95 0.6 0",
	"1 1 0",
	"0 0.57 0.28",
	"0 0.53 0.88",
	"0.25 0.10 0.55"
};
#else
int n=8; char *colors[]={"1 0 0","1 1 0","0 0.57 0.28","0 0.53 0.88"};
#endif

double R=100, pi=2*acos(0.), EPS=1e-8;

struct pt { double x,y; };
pt operator -(pt a, pt b) { pt c={a.x-b.x,a.y-b.y}; return c; }
double skew(pt a, pt b) { return a.x*b.y-a.y*b.x; }
double dist2(pt a) { return a.x*a.x+a.y*a.y; }

pt vert(int k) { double a=2*pi*k/n; pt p={R*cos(a),R*sin(a)}; return p; }

pt isect(pt a, pt b, pt c, pt d) {
	double a1=a.y-b.y, b1=b.x-a.x, c1=a1*a.x+b1*a.y;
	double a2=c.y-d.y, b2=d.x-c.x, c2=a2*c.x+b2*c.y;
	double D=a1*b2-a2*b1;
	pt p={(c1*b2-c2*b1)/D,(a1*c2-a2*c1)/D};
	return p;
}

/* gift-wrapping algorithm; returns a convex polygon 'h' with vertices
   in ccw order; h[0]==h[h.size()-1]. */
/* NOT ROBUST */
vector<pt> hull(vector<pt> p)
{
	vector<pt> h;
	int i, j, k, n = p.size();

	if (n <= 1) return p;

	for (i = j = 0; i < n; i++)
		if (p[i].x < p[j].x-EPS ||
		    (fabs(p[i].x-p[j].x)<EPS && p[i].y < p[j].y-EPS)) j = i;
	h.push_back(p[j]);

	for (k = 0;; k++) {
		for (i = 0, j = -1; i < n; i++) {
			if (dist2(p[i] - h[k]) < EPS) continue;
			if (j < 0) { j=i; continue; }
			double t = skew(p[i]-h[k], p[j]-h[k]);
			if (t>EPS || (fabs(t)<EPS && dist2(h[k]-p[j]) > dist2(h[k]-p[i]))) j = i;
		}
		if (j < 0) break;
		if (dist2(p[j] - h[0]) < EPS) break;
		h.push_back(p[j]);
	}	

	h.push_back(h[0]);
	return h;
}

void fillreg(int delta)
{
	vector<pt> h;

	for (int i = 0; i < n; i++)
		h.push_back(isect(
			vert(i), vert(i+delta),
			vert(i+1), vert(i+1+delta)));
	h = hull(h);

	printf("newpath %.9lf %.9lf moveto\n", h[0].x, h[0].y);
	for (int i = 1; i < h.size(); i++)
		printf("%.9lf %.9lf lineto\n", h[i].x, h[i].y);
	printf("closepath fill\n");
}

int main()
{
	printf("%.9lf %.9lf translate\n", 2.5*R, 2.5*R);

	printf("%s setrgbcolor\n", colors[0]);
	printf("newpath %.9f 0 moveto 0 0 %.9f 0 360 arc closepath fill\n",R,R);

	for (int d = 1; d <= n/2-1; d++) {
		printf("%s setrgbcolor\n", colors[d]);
		fillreg(d);
	}	

	printf("0 setgray 1 setlinewidth\n");
	printf("%.9f 0 moveto 0 0 %.9f 0 360 arc stroke\n", R, R);
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			pt p=vert(i), q=vert(j);
			printf("%.9lf %.9lf moveto %.9lf %.9lf lineto stroke\n", p.x, p.y, q.x, q.y);
		}
	}

	return 0;
}
