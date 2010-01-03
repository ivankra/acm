#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define F(x) (p*exp(-(x)) + q*sin(x) + r*cos(x) + s*tan(x) + t*(x)*(x) + u)
#define ISZ(x) (((x) > -0.000001) && ((x) < 0.000001))

int main()
{
	static int pi, qi, ri, si, ti, ui;
	double p, q, r, s, t, u;
	double a, b, c, f;

	while (scanf("%d %d %d %d %d %d", &pi, &qi, &ri, &si, &ti, &ui) >= 6) {
		p = pi; q = qi; r = ri; s = si; t = ti; u = ui;

		f = F(0.);
		if (ISZ(f)) { printf("0.0000\n"); continue; }
		if (f < 0.) { printf("No solution\n"); continue; }

		f = F(1.);
		if (ISZ(f)) { printf("1.0000\n"); continue; }
		if (f > 0.) { printf("No solution\n"); continue; }

		for (a = 0., b = 1.;;) {
			c = 0.5 * (a + b);
			f = F(c);

			if (ISZ(f)) {
				printf("%.4f\n", c);
				break;
			}

			if (f > 0.)
				a = c;
			else
				b = c;
		}
	}

	return 0;
}
