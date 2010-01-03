#include <stdio.h>

int sum(int x)
{
	int s;

	for (s = 0; x > 0; x /= 10)
		s += (x % 10);

	return s;
}

int isqrt(int a)
{
	int x, y;

	if (a < 4) return 1;

	for (x = a;; x = y) {
		y = (((a / x) + x) >> 1);
		if (y >= x) return x;
	}
}

int test(int x)
{
	int s, r, d, m;

	r = sum(x);
	m = isqrt(x) + 1;

	for (d = 2, s = 0; d <= m; d = (d == 2) ? 3 : (d + 2)) {
		if ((x % d) != 0)
			continue;

		if (d == x)
			break;

		while ((x % d) == 0) {
			x /= d;
			s += sum(d);
		}

		m = isqrt(x) + 1;
	}

	if (s == 0)
		return 0;

	if (x > 1)
		s += sum(x);

	return (r == s);
}

int main()
{
	int n, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		while (test(++n) == 0);
		printf("%d\n", n);
	}

	return 0;
}
