#include <stdio.h>
#include <math.h>

typedef struct { int x, y; } pair;
pair P(int x, int y) { pair p; p.x = x; p.y = y; return p; }

double dist(pair a, pair b)
{
	double u = a.x - b.x, v = a.y - b.y;
	return sqrt(u * u + v * v);
}

int isqrt(int a)
{
	int x, y;
	for (x = a; x > 1; x = y)
		if ((y = (x + a / x) >> 1) >= x) break;
	return x;
}

pair get(int a)
{
	int r;

	if (a < 1) return P(0,0);

	r = (isqrt(2 * a - 1) - 1) / 2;
	while (2*r*r+2*r+1 <= a) r++;

	a -= 2*(r-1)*(r-1)+2*r-1;
	a = (a + 3*r + 1) % (4*r);

	if (a < r)
		return P(a, r-a);
	else if (a < 2*r)
		return P(2*r-a, r-a);
	else if (a < 3*r)
		return P(2*r-a, a-3*r);
	else
		return P(a-4*r, a-3*r);
}

int main()
{
	int a, b;
	while (scanf("%d %d", &a, &b) == 2 && a >= 0 && b >= 0)
		printf("%.2f\n", dist(get(a), get(b)));
	return 0;
}
