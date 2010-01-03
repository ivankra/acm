#include <stdio.h>
#include <math.h>

#define EPS 1e-9

double ha, hb, hc, a, b, c, t, s;
int n;

int solve()
{
	if (ha < EPS || hb < EPS || hc < EPS) return 1;

	a = 1.;
	b = ha / hb;
	c = ha / hc;

	if (a > (b + c - EPS)) return 1;
	if (b > (a + c - EPS)) return 1;
	if (c > (a + b - EPS)) return 1;

	t = hb / (2 * ha) + ha / (2 * hb) - ha * hb / (2 * hc * hc);
	if (t < (-1 - EPS) || t > (1 + EPS)) return 1;
	if (t < -1) t = -1;
	if (t > 1) t = 1;

	t = hb / sqrt(1 - t * t);
	a *= t;
	b *= t;
	c *= t;

	t = (a + b + c) / 2;
	s = sqrt(t * (t - a) * (t - b) * (t - c));
	if (s < EPS) return 1;

	return 0;
}

int main()
{
	for (scanf("%d", &n); n > 0 && scanf("%lf %lf %lf", &ha, &hb, &hc) == 3;)
		if (solve())
			n--, printf("These are invalid inputs!\n");
		else
			printf("%.3f\n", s);
	return 0;
}
