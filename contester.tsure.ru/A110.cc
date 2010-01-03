#include <cstdio>

struct Point { int x, y; };

long double cross(const Point &a, const Point &b) {
	return a.x*(long double)b.y - a.y*(long double)b.x;
}

int main()
{
	int n;
	Point P, Q, S;
	long double a = 0;

	scanf("%d %d %d", &n, &P.x, &P.y); S=P;
	for (int i = 1; i < n; i++) {
		Q = P;
		scanf("%d %d", &P.x, &P.y);
		a += cross(Q, P);
	}
	a += cross(P, S);
	printf(a>=0?"ccw\n":"cw\n");

	return 0;
}
