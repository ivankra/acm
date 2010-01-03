#include <stdio.h>

static int isqrt(int a)
{
	register int x, y;

	for (x = a; x > 1; x = y)
		if ((y = ((x + (a / x)) >> 1)) >= x) return x;

	return x;
}

int main()
{
	static int n, r;
	int d, p, m;

/*	phi(p^n) = p^(n-1) (p - 1), p prime
	phi(a b) = phi(a) phi(b), if gcd(a,b) == 1
*/

	while (scanf("%d", &n) == 1 && n > 0) {
		if (n == 1) {
			printf("0\n");
			continue;
		}

		for (p = 0; (n & 1) == 0; n >>= 1, p++);
		r = (p == 0) ? 1 : (1 << (p - 1));

		m = isqrt(n) + 1;
		for (d = 3; d <= m; d += 2) {
			if ((n % d) == 0) {
				for (n /= d, p = 1; (n % d) == 0; n /= d, p++)
					r *= d;
				r *= d - 1;
				m = isqrt(n) + 1;
			}
		}

		if (n > 1)
			r *= (n - 1);

		printf("%d\n", r);
	}

	return 0;
}
