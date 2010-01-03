#include <cstdio>
#include <cstdlib>

struct pos {
	int x, y;
	pos(int x, int y) : x(x), y(y) {}
	pos operator -(const pos &b) const { return pos(x-b.x, y-b.y); }
};

/* x axis: 1-7-19-...
   y axis: 1-5-15-... */

pos where(int n)
{
	int r;

	if (n == 1) return pos(0, 0);

	for (r = 1; 1+3*r*(r-1) < n; r++);
	n -= 1+3*(r-1)*(r-2); r--;

	if (n <= r) return pos(r-n, -n);
	if (n <= 2*r) return pos(r-n, -r);
	if (n <= 3*r) return pos(-r, n-3*r);
	if (n <= 4*r) return pos(n-4*r, n-3*r);
	if (n <= 5*r) return pos(n-4*r, r);
	return pos(r, 6*r-n);
}

int solve(int a, int b) {
	pos d = where(a) - where(b);

	if (d.x * d.y >= 0)
		return abs(d.x) >? abs(d.y);
	else
		return abs(d.x) + abs(d.y);
}

int main()
{
	int a, b;
	while (scanf("%d %d", &a, &b) == 2 && a > 0 && b > 0)
		printf("The distance between cells %d and %d is %d.\n", a, b, solve(a, b));
	return 0;
}
