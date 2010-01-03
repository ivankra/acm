#include <stdio.h>

int solve(double H, double V, double h, double v, double x, double y)
{
	for (int r = 0;; r ^= 1) {
		if (x < H*h && y < V*v) {
			H *= h;
			V *= v;
		} else if (x > H*h && y > V*v) {
			x -= H*h;
			y -= V*v;
			H *= 1-h;
			V *= 1-v;
		} else {
			return r;
		}
	}	
}

int main()
{
	double H, V, h, v, x, y;
	int n;
	for (int cs = 1; scanf(" %lf %lf %lf %lf %d", &H, &V, &h, &v, &n) == 5; cs++) {
		printf("Case %d:\n", cs);
		while (n-- > 0 && scanf(" %lf %lf", &x, &y) == 2)
			printf(solve(H, V, h, v, x, y) ? "white\n" : "black\n");
	}
	return 0;
}
