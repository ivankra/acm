#include <stdio.h>
#include <math.h>

#define EPS 1e-8

double a, b, c[2], alpha, beta, pi;

int solve()
{
	double s, t, u, v;

	while (beta < -EPS) beta += 2 * pi;
	while (beta > (2 * pi + EPS)) beta -= 2 * pi;
	if (fabs(beta) < EPS || fabs(beta - 2 * pi) < EPS) beta = 0.;

	if (a < EPS || b < EPS) return 0;

	if (fabs(beta) < EPS) {
		c[0] = a - b;
		c[1] = a + b;
	} else if (fabs(beta - pi) < EPS) {
		c[0] = b - a;
		c[1] = b - a;
	} else {
		if (beta > (pi - EPS)) return 0;

		s = sin(beta);
		t = a * s / b;
		if (t < (-1. - EPS)) return 0;
		if (t < -1.) t = -1.;
		if (t > (1. + EPS)) return 0;
		if (t > 1.) t = 1.;

		u = sqrt(1 - t * t) * b;
		v = cos(beta) * t * b / s;
		c[0] = v + u;
		c[1] = v - u;
	}

	if (c[0] < EPS && c[1] < EPS)
		return 0;

	if (c[0] < EPS) {
		c[0] = c[1];
		return 1;
	}

	if (c[1] < EPS) {
		c[1] = c[0];
		return 1;
	}

	return 1;
}

int main()
{
	int t;

	printf("Case    A      B    THETA  # of    Side   Side\n"
	       " #     side   side  (deg)  Triags    1      2\n");

	pi = 2. * acos(0.);

	for (t = 0; scanf("%lf %lf %lf", &a, &b, &beta) == 3;) {
		if (fabs(a) < EPS && fabs(b) < EPS && fabs(beta) < EPS) break;
		printf("%4d%7.2f%7.2f%7.2f     ", ++t, a, b, beta);

		beta *= pi / 180.;

		if (solve() == 0)
			printf("0\n");
		else if (fabs(c[0] - c[1]) < EPS)
			printf("1%9.2f\n", c[0]);
		else if (c[0] > c[1])
			printf("2%9.2f%7.2f\n", c[0], c[1]);
		else
			printf("2%9.2f%7.2f\n", c[1], c[0]);
	}

	printf("\nEND OF REPORT for %d cases\n", t);
	return 0;
}
