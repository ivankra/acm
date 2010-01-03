#include <stdio.h>

#define N 13

int gcd(int x, int y) { return (x == 0) ? y : gcd(y % x, x); }
int lcm(int x, int y) { return (x / gcd(x, y)) * y; }

int main()
{
	int x[N], y[N], z[N], p, q, r, i, j;

	for (q = 1, j = 0; j < N; q++) {
		for (p = -q; j < N && p <= q; p++) {
			for (r = -q; j < N && r <= q; r++) {
				if ((p * p + r * r) != (q * q))
					continue;

				x[j] = q * q - 2 * p * p;
				y[j] = 2 * p * r;
				z[j] = q * q;

				for (i = 0; i < j; i++)
					if ((x[i] * z[j]) == (x[j] * z[i]) &&
					    (y[i] * z[j]) == (y[j] * z[i]))
						break;

				if (i == j)
					j++;
			}
		}
	}

	for (r = 1, i = 0; i < N; i++)
		r = lcm(r, z[i]);

	for (i = p = q = 0; i < N; i++) {
		x[i] *= r / z[i];
		y[i] *= r / z[i];
		if (x[i] < p) p = x[i];
		if (y[i] < q) q = y[i];
	}

	for (i = 0; i < N; i++) {
		x[i] -= p;
		y[i] -= q;
	}

	for (i = 0; i < N; i++)
		printf("%d %d\n", x[i], y[i]);

	return 0;
}
