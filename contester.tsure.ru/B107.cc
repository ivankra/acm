#include <cstdio>
#include <cmath>

int main()
{
	struct { double x, y; } p, q;
	int n;
	scanf("%d %lf %lf", &n, &p.x, &p.y);
	for (; n-- > 0 && scanf("%lf %lf", &q.x, &q.y) == 2; p = q)
		printf("%.3f\n", hypot(p.x-q.x, p.y-q.y));
}
