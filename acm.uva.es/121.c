#include <stdio.h>
#include <math.h>

#define EPS 1e-12

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int grid(double a, double b)
{
	return (((int)floor(a + EPS)) * (int)floor(b + EPS));
}

int skew(double a, double b)
{
	int m1, m2, n;

	m1 = floor(b + EPS);
	m2 = floor(b - 0.5 + EPS);

	n = floor(2. * (a - 1) * sqrt(3.) / 3. + 1 + EPS);

	if (n <= 0)
		return 0;

	return ((n >> 1) * (m1 + m2) + (n & 1) * m1);
}

int main()
{
	double a, b;
	int g, s;

	while (scanf("%lf %lf", &a, &b) == 2) {
		g = grid(a, b);
		s = max(skew(a, b), skew(b, a));
		printf("%d %s\n", max(g, s), (g >= s) ? "grid" : "skew");
	}

	return 0;
}
