#include <stdio.h>
#include <math.h>

double pi2;

int check(double w, double h, double m, double n)
{
	double t, y, z;

	if (w > (m - 1e-6) || w > (n - 1e-6))
		return 0;

	for (z = 1e20, t = 1e-4; t < (pi2 - 1e-4); t += 1e-3) {
		y = m * sin(t) + n * cos(t) - 0.5 * h * sin(2 * t);
		if (y < z) z = y;
	}

	return (w < (z + 1e-6));
}

int main()
{
	static char s[131072];
	double w, h, a, b;
	int n, m;

	pi2 = acos(0.);

	while (gets(s)) {
		if (sscanf(s, "%lf,%lf%n", &w, &h, &n) < 2) continue;

		for (; sscanf(s + n, "%lf,%lf%n", &a, &b, &m) >= 2; n += m)
			if (check(w, h, a, b) || check(h, w, a, b))
				printf("Y");
			else
				printf("N");

		printf("\n");
	}

	return 0;
}
