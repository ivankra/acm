#include <stdio.h>

static int int_sqrt(int n)
{
	register int x, y;
	for (x = n;;) {
		if (x == 0) return 0;
		y = (x + (n / x)) >> 1;
		if (y >= x) return x;
		x = y;
	}
}

static int sigma0(int n)
{
	int r, i, m;

	if (n <= 1) return 1;

	for (i = 0; (n & 1) == 0; i++, n >>= 1);
	r = (i + 1);

	m = int_sqrt(n) + 16;
	for (i = 3; i <= m && n > 1; i += 2) {
		register int j;

		for (j = 0; (n % i) == 0; j++, n /= i);

		if (j == 0)
			continue;

		r *= (j + 1);
		m = int_sqrt(n) + 16;
	}

	if (n > 1)
		r *= 2;		/* prime divisor `n' ^ 1 */

	return r;
}

int main(void)
{
	int u, l, n, i, m, md, d;

	scanf("%d", &n);
	while (n-- > 0) {
		scanf("%d %d", &l, &u);

		for (i = l; i <= u; i++) {
			d = sigma0(i);
			if (i == l || d > md) {
				m = i;
				md = d;
			}
		}

		printf("Between %d and %d, %d has a maximum of %d divisors.\n",
			l, u, m, md);
	}

	return 0;
}
