#include <cstdio>
#include <cmath>

int main()
{
	int a, b, v, A, s;
	double PI = 2*acos(0.0);

	while (scanf("%d %d %d %d %d", &a, &b, &v, &A, &s) == 5) {
		if ((a|b|A|s) == 0) break;

		double r = v * (double)s;
		double dx = r*cos(A*PI/180.0);
		double dy = r*sin(A*PI/180.0);

		int x = (int)floor(dx/(2.0*a)+0.5+1e-6);
		int y = (int)floor(dy/(2.0*b)+0.5+1e-6);

		printf("%d %d\n", x, y);
	}
}
