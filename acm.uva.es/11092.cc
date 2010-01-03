#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

// x: right, y: up-right
void get(int &x, int &y, int k) {
	x = y = 0;
	if (k == 0) return;

	k--;

	int r;
	for (r = 1; 6*r <= k; r++)
		k -= 6*r;

	x = r;
	y = 1 - r;

	int dx[] = { 0, -1, -1, 0, 1, 1 };
	int dy[] = { 1, 1, 0, -1, -1, 0 };

	for (int i = 0; i < 6; i++) {
		int d = min(k, r - (i==0 ? 1 : 0));
		x += d * dx[i];
		y += d * dy[i];
		k -= d;
	}
}

double dist(double x, double y) { return sqrt(x*x+y*y); }

int main() {
	double ang = 4.0*acos(0.0)/6.0, ca = cos(ang), sa = sin(ang);
	int a, b;
	while (scanf("%d %d", &a, &b) == 2) {
		int au, av, bu, bv;
		get(au,av,a);
		get(bu,bv,b);

		int u=bu-au, v=bv-av;
		printf("%d.000 %.3f\n", abs(a-b), dist(u+v*ca, v*sa));
	}
}
