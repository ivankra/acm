#include <stdio.h>

static int isqrt(int a)
{
	register int x, y;

	for (x = a; x > 1; x = y)
		if ((y = ((x + (a / x)) >> 1)) >= x) return x;

	return x;
}

static int phi(int n)
{
	register int r, d, p, m;

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

	return r;
}

int main()
{
	static int tab[50002], n;
	int i;

	for (tab[1] = 1, i = 2; i <= 50000; i++)
		tab[i] = tab[i - 1] + 2 * phi(i);

	while (scanf("%d", &n) == 1 && n > 0)
		printf("%d\n", tab[n]);

	return 0;
}
