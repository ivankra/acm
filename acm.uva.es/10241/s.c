#include <stdio.h>
#include <stdlib.h>

#define BRUTE_BOUND 1000000000

static long long int_sqrt(long long n)
{
	register long long x, y;

	for (x = n; x > 0; x = y) {
		y = (x + (n / x)) >> 1;
		if (y >= x)
			return x;
	}

	return 0;
}

static long long gcd(long long x, long long y)
{
	long long t;

	while (y > 0) {
		t = x % y;
		x = y;
		y = t;
	}

	return x;
}

int main(int argc, char *argv[])
{
	long long x, y, k, x0, y0, x1, y1, x2, y2, l, g;
	long long p, q, r, s, t, u;
	int i;

	setvbuf(stdout, NULL, _IONBF, 0);

	k = (argc > 1) ? atoi(argv[1]) : 1;

	printf("Solving: k x^2 + k x = 2 y^2, k = %d\n\n", (int)k);

	printf("Assuming roots are of form:\n");
	printf("  x[n+1] = p x[n] + q y[n] + r\n");
	printf("  y[n+1] = s x[n] + t y[n] + u\n\n");

	printf("Trivial root: x=0, y=0\n\n");
	printf("Brute force for non-trivial roots...\n");

	for (x0 = 1;; x0++) {
		if (x0 > BRUTE_BOUND) { printf("Bound exceeded\n"); exit(1); }
		y0 = int_sqrt(l = k * ((x0 * (x0 + 1)) >> 1));
		if ((y0 * y0) == l)
			break;
	}

	printf("Found pair: x=%.0f, y=%.0f\n", (double)x0, (double)y0);

	r = x0;
	u = y0;
	printf("Implies: r=%.0f, u=%.0f\n", (double)x0, (double)y0);

	printf("  x[n+1] = p x[n] + q y[n] + %.0f\n", (double)r);
	printf("  y[n+1] = s x[n] + t y[n] + %.0f\n\n", (double)u);

	for (x1 = x0+1;; x1++) {
		if (x1 > BRUTE_BOUND) { printf("Bound exceeded\n"); exit(1); }
		y1 = int_sqrt(l = k * ((x1 * (x1 + 1)) >> 1));
		if ((y1 * y1) == l)
			break;
	}

	printf("Found pair: x=%.0f, y=%.0f\n", (double)x1, (double)y1);

	printf("  %.0f p + %.0f q + %.0f = %.0f\n",
		(double)x0, (double)y0, (double)r, (double)x1);
	printf("  %.0f s + %.0f t + %.0f = %.0f\n\n",
		(double)x0, (double)y0, (double)u, (double)y1);

	printf("  %.0f p + %.0f q = %.0f\n",
		(double)x0, (double)y0, (double)(x1 - r));
	printf("  %.0f s + %.0f t = %.0f\n\n",
		(double)x0, (double)y0, (double)(y1 - u));


/*
x2 = x1 p + y1 q + r
x1 p + y1 q = (x2 - r)
x1 p = (x2 - r) - y1 q

x1 = x0 p + y0 q + r
(x1 - r) = x0 p + y0 q
x0 p = (x1 - r) - y0 q

x2 = x1 p + y1 q + r

*/
	for (q = 0;; q++) {
		p = x1 - r - y0 * q;
		if (p < 0 && q > 0) break;
		if ((p % x0) != 0) continue;
		p /= x0;

		x2 = p * x1 + q * y1 + r;

		l = k * ((x2 * (x2 + 1)) >> 1);
		y2 = int_sqrt(l);
		if ((y2 * y2) != l) { continue; }

		printf("  p=%.0f q=%.0f r=%.0f  x2=%.0f y2=%.0f\n",
			(double)p, (double)q, (double)r,
			(double)x2, (double)y2);
		break;
	}

/*
y1 = s x0 + t y0 + u
t y0 = y1 - u - s x0

y2 = s x1 + t y1 + u

*/

	for (s = 0;; s++) {
		t = y1 - u - s * x0;
		if (t < 0 && q > 0) break;
		if ((t % y0) != 0) continue;
		t /= y0;

		l = s * x1 + t * y1 + u;
//printf("[s=%.0f y2=%.0f  y2_=%.0f]\n", (double)s, (double)l, (double)y2);
		if (l == y2) {
			printf("  s=%.0f t=%.0f u=%.0f\n",
				(double)s, (double)t, (double)u);
		}
	}

	return 0;
}
