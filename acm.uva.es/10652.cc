#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

#define EPS 1e-8

struct pt { double x,y; };
pt operator +(pt a, pt b) { pt c={a.x+b.x,a.y+b.y}; return c; }
pt operator -(pt a, pt b) { pt c={a.x-b.x,a.y-b.y}; return c; }
double skew(pt a, pt b) { return a.x*b.y-a.y*b.x; }
double dist2(pt a) { return a.x*a.x+a.y*a.y; }

vector<pt> hull_prep(vector<pt> p)
{
	int n = p.size();
	vector<pt> q; pt a,b,c,d;

	a=b=c=d=p[0];
	for (int i = 0; i < n; i++) {
		if (p[i].x < a.x-EPS || (fabs(p[i].x-a.x)<EPS && p[i].y<a.y)) a=p[i];
		if (p[i].y < b.y-EPS || (fabs(p[i].y-b.y)<EPS && p[i].x>b.x)) b=p[i];
		if (p[i].x > c.x-EPS || (fabs(p[i].x-c.x)<EPS && p[i].y>c.y)) c=p[i];
		if (p[i].y > d.y-EPS || (fabs(p[i].y-d.y)<EPS && p[i].x<d.x)) d=p[i];
	}

	for (int i = 0; i < n; i++)
		if (skew(a-p[i],b-p[i]) < EPS || skew(b-p[i],c-p[i]) < EPS ||
		    skew(c-p[i],d-p[i]) < EPS || skew(d-p[i],a-p[i]) < EPS)
			q.push_back(p[i]);

	return q;
}

bool cmp(pt p, pt q) { return p.x < q.x-EPS || (p.x < q.x+EPS && p.y < q.y); }

vector<pt> hull(vector<pt> p)
{
	if (p.size() <= 1) return p;

	vector<pt> q=hull_prep(p); vector<pt> h;
	sort(q.begin(), q.end(), cmp);

	int n = q.size(), k = 0;
	for (int i = 0; i < n; i++) {
		while (k >= 2 && skew(h[k-1]-h[k-2], q[i]-h[k-2]) < EPS)
			k--, h.pop_back();
		k++, h.push_back(q[i]);
	}

	int t = max(k+1,2);
	for (int i = n-2; i >= 0; i--) {
		while (k >= t && skew(h[k-1]-h[k-2], q[i]-h[k-2]) < EPS)
			k--, h.pop_back();
		k++, h.push_back(q[i]);
	}	

	return h;
}

double area(vector<pt> p)
{
	double r = 0;
	for (int i = 0; i < p.size()-1; i++)
		r += skew(p[i], p[i+1]);
	return fabs(r)/2.;
}

int main()
{
	int n, T;
	double s, x, y, w, h, a, pi=2.*acos(0.);
	vector<pt> p;

	for (scanf("%d", &T); T-- > 0 && scanf("%d", &n) == 1;) {
		s = 0;
		p.clear();
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf %lf %lf %lf", &x, &y, &w, &h, &a);
			s += w * h;
			a *= pi / 180.;
			pt z = { x, y };
			pt u = { h*sin(a)/2, h*cos(a)/2 };
			pt v = { w*cos(a)/2, -w*sin(a)/2 };
			p.push_back(z+u+v); p.push_back(z+u-v);
			p.push_back(z-u+v); p.push_back(z-u-v);
		}
		printf("%.1f %%\n", s*100/area(hull(p)));
	}

	return 0;
}
