#include <stdio.h>

static unsigned solve(unsigned long long n, unsigned m)
{
	unsigned i, a, b, t;

	if (m <= 1) return 0;
	if (n <= 1) return 1;

	n--;
	a = 1;
	b = 0;

	for (i = 0; (n >> (i + 1)) > 0; i++);

	while (i--) {
		t = (a * a + b * b) % m;
		a = ((a + 2 * b) * a) % m;
		b = t;

		if ((n >> i) & 1) {
			t = a;
			a += b;
			if (a >= m) a -= m;
			b = t;
		}
	}

	return (4 * a + 2 * b + m - 1) % m;
}

int main()
{
	unsigned long long n;
	unsigned t, m;

	for (t = 1; scanf("%llu %u", &n, &m) == 2 && m != 0; t++)
		printf("Case %u: %llu %u %u\n",t, n, m, solve(n, m));

	return 0;
}
