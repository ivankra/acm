#include <cstdio>
#include <cmath>
#include <set>
#include <queue>
using namespace std;
#define EPS 1e-12

struct tri { double b, c; };

bool operator <(tri u, tri v) { return u.b<v.b-EPS || (u.b<v.b+EPS && u.c<v.c-EPS); }

tri make(double A, double B, double C)
{
	if (A < B) return make(B, A, C);
	if (B < C) return make(A, C, B);
	tri t={B/A, C/A};
	return t;
}

int count(tri s)
{
	set<tri> w;
	queue<tri> q;

	w.insert(s);
	for (q.push(s); !q.empty(); q.pop()) {
        	s = q.front();

/*printf("1 : sqrt(%.10f) : sqrt(%.10f)\n", s.b, s.c);*/

        	double m = (2*s.b + 2*s.c - 1) / 4;
        	if (m < EPS) continue;

		s = make(q.front().b, 0.25, m);
		if (w.count(s) == 0) { w.insert(s); q.push(s); }

		s = make(q.front().c, 0.25, m);
		if (w.count(s) == 0) { w.insert(s); q.push(s); }
	}

	return w.size();
}

int main()
{
	int a, b, c, t, T;
	for (scanf("%d", &T), t=1; t<=T && scanf("%d%d%d",&a,&b,&c)==3; t++)
		printf("Triangle %d: %d\n", t, count(make(a*a,b*b,c*c)));
	return 0;
}
