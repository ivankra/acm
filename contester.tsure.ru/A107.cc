#include <cstdio>
#include <cstring>

struct Point { long long x, y; };
void read(Point &p) { scanf("%lld %lld", &p.x, &p.y); }

long long cross(Point &o, Point &a, Point &b) {
	return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}

int sgn(long long x) { return x==0?0:(x<0?-1:1); }

int on(Point &a, Point &b, Point &p) {
	if (a.x == b.x && a.y == b.y) return (a.x == p.x && a.y == p.y);
	if (cross(a,b,p) != 0) return 0;
	Point a1={a.x-(b.y-a.y), a.y+(b.x-a.x)};
	Point b1={b.x-(b.y-a.y), b.y+(b.x-a.x)};
	if (sgn(cross(a,a1,b))*sgn(cross(a,a1,p)) < 0) return 0;
	if (sgn(cross(b,b1,a))*sgn(cross(b,b1,p)) < 0) return 0;
	return 1;
}

int segmentsCross(Point &a, Point &b, Point &c, Point &d) {
	if (on(a,b,c) || on(a,b,d) || on(c,d,a) || on(c,d,b)) return 1;
	if (sgn(cross(a,b,c))*sgn(cross(a,b,d)) > 0) return 0;
	if (sgn(cross(c,d,a))*sgn(cross(c,d,b)) > 0) return 0;
	if (cross(a,b,c) != 0 || cross(a,b,d) != 0) return 1;
	return 0;

}

int main()
{
	Point P[1024], A[1024], B[1024];
	int ok[1024], n, m;

	scanf("%d %d", &n, &m);
	for (int i = 0; i <= n; i++) read(P[i]);
	for (int i = 0; i < m; i++) { read(A[i]); read(B[i]); ok[i] = 0; }

	for (int i = 0; i < n; i++)
	for (int j = 0; j < m; j++)
		if (segmentsCross(P[i],P[i+1], A[j],B[j])) ok[j]=1;

	int k = 0;
	for (int i = 0; i < m; i++)
		if (ok[i]) printf(k++?" %d":"%d", i+1);
	printf(k?"\n":"OK\n");
}
