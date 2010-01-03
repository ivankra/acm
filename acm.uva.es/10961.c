#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INF 0x7FFFFFFF

typedef struct { int x, y; } pt;

pt a[128], b[128];
int n, m;

int min(int x, int y) { return (x < y) ? x : y; }
int max(int x, int y) { return (x > y) ? x : y; }
int sgn(int x) { return (x > 0) ? 1 : ((x < 0) ? -1 : 0); }
int dist(pt p, pt q) { return abs(p.x - q.x) + abs(p.y - q.y); }
long long gcd(long long x, long long y) { return y ? gcd(y, x % y) : x; }

int isect(pt p1, pt p2, pt q1, pt q2)
{
/*
   x = p1.x + t/P (p2.x - p1.x)
   y = p1.y + t/P (p2.y - p1.y)
   x = q1.x + t/Q (q2.x - q1.x)
   y = q1.y + t/Q (q2.y - q1.y)

   t/P (p2.x - p1.x) + t/Q (q1.x - q2.x) = q1.x - p1.x
   t/P (p2.y - p1.y) + t/Q (q1.y - q2.y) = q1.y - p1.y

   t (Q p2.x - Q p1.x + P q1.x - P q2.x) = PQ(q1.x - p1.x)
   t (Q p2.y - Q p1.y + P q1.y - P q2.y) = PQ(q1.y - p1.y)

   t (Q p2.x - Q p1.x + P q1.x - P q2.x) = PQ(q1.x - p1.x)
   t (Q p2.y - Q p1.y + P q1.y - P q2.y) = PQ(q1.y - p1.y)

   at=c
   bt=d

   t = c/a = d/b
*/
	long long a, b, c, d, g, Q, P;

	P = dist(p1, p2);
	Q = dist(q1, q2);

	a = Q * (p2.x - p1.x) + P * (q1.x - q2.x); c = P * Q * (q1.x - p1.x);
	b = Q * (p2.y - p1.y) + P * (q1.y - q2.y); d = P * Q * (q1.y - p1.y);

	if (a < 0) { a = -a; c = -c; }
	if (b < 0) { b = -b; d = -d; }

/*printf("(%d,%d)->(%d,%d), (%d,%d)->(%d,%d)  ==>  ",
  p1.x,p1.y, p2.x,p2.y,
  q1.x,q1.y, q2.x,q2.y);
printf("%lldt=%lld %lldt=%lld\n", a,c, b,d);
*/
	if (a == 0) { if (b != 0) return INF; a = b; c = d; }
	if (b == 0) { if (d != 0) return INF; b = a; d = c; }

	if (c < 0 || d < 0) return INF;
	if (a == 0 || b == 0) return INF;

	g = gcd(a, c); a /= g; c /= g;
	g = gcd(d, b); d /= g; b /= g;
	if (a != b || c != d) return INF;

	return (int)(c / a);
}

int solve()
{
	int i, j, t;

	for (i = j = 0;;) {
		if (i >= n || j >= m) break;

		if (a[i].x == a[i+1].x && a[i].y == a[i+1].y) { i++; continue; }
		if (b[j].x == b[j+1].x && b[j].y == b[j+1].y) { j++; continue; }

		if (a[i].x == b[j].x && a[i].y == b[j].y) return 0;

		t = min(dist(a[i], a[i+1]), dist(b[j], b[j+1]));
		t = min(t, isect(a[i], a[i+1], b[j], b[j+1]));

		a[i].x += t * sgn(a[i+1].x - a[i].x);
		a[i].y += t * sgn(a[i+1].y - a[i].y);
		b[j].x += t * sgn(b[j+1].x - b[j].x);
		b[j].y += t * sgn(b[j+1].y - b[j].y);
	}

	return 1;
}

int main()
{
	int i, t;

	for (scanf("%d", &t); t-- > 0;) {
		scanf("%d %d %d %d", &b[0].x, &b[0].y, &a[0].x, &a[0].y);

		scanf("%d", &n);
		assert(n <= 125);
		for (i = 1; i <= n; i++) scanf("%d %d", &a[i].x, &a[i].y);

		scanf("%d", &m);
		assert(m <= 125);
		for (i = 1; i <= m; i++) scanf("%d %d", &b[i].x, &b[i].y);

		printf("%s%s", solve() ? "Yes\n" : "No\n", t ? "\n" : "");
	}

	return 0;
}
