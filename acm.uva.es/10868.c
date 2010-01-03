#include <stdio.h>
#include <math.h>

#define EPS 1e-12

double k, l, s, w, g = 9.81;

char *solve()
{
	double a, c, d, t, v, x, dt;

	if (s < (l + EPS)) {
		if ((s * g) > (50. + EPS))
			return "Killed by the impact.";
		else
			return "James Bond survives.";
	}

	t = sqrt(2. * l / g);
	v = g * t;
	x = g * t * t / 2.;
	a = g;
	c = g + k * l / w;
	d = k / w;

	dt = 0.0001;
	for (;;) {
		if (x > (s - EPS))
			break;

		if (v < 0)
			return "Stuck in the air.";

		x += v * dt;
		v += a * dt;
		a = c - d * x;
		t += dt;
	}

	if (v > (10. + EPS))
		return "Killed by the impact.";
	else
		return "James Bond survives.";
}

int main()
{
	while (scanf("%lf %lf %lf %lf", &k, &l, &s, &w) == 4) {
		if (k < EPS && l < EPS && s < EPS && w < EPS)
			break;

		printf("%s\n", solve());
	}

	return 0;
}
