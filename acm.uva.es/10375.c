#include <stdio.h>

int main()
{
	int p1, p2, p3, q1, q2, q3, n1, n2, n3, m1, m2, m3, p, q, r, s;
	long double x;

	while (scanf("%d %d %d %d", &p, &q, &r, &s) == 4) {
		n1 = p;
		n2 = s;
		n3 = r - s;
		m1 = q;
		m2 = r;
		m3 = p - q;

		p1 = p2 = p3 = q1 = q2 = q3 = 1;
		x = 1.;
		do {
			s = 0;
			while (p1 <= n1) { s = 1; x *= (long double)p1; p1++; if (x > 1e8) break; }
			while (p2 <= n2) { s = 1; x *= (long double)p2; p2++; if (x > 1e8) break; }
			while (p3 <= n3) { s = 1; x *= (long double)p3; p3++; if (x > 1e8) break; }
			while (q1 <= m1) { s = 1; x /= (long double)q1; q1++; if (x < 1) break; }
			while (q2 <= m2) { s = 1; x /= (long double)q2; q2++; if (x < 1) break; }
			while (q3 <= m3) { s = 1; x /= (long double)q3; q3++; if (x < 1) break; }
		} while (s > 0);

		printf("%.5Lf\n", x);
	}

	return 0;
}
