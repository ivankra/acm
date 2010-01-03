#include <stdio.h>
#include <stdlib.h>

typedef struct {
	long long p, q;
} rat_t;

long long m, n;
rat_t t1, t2;

void solve()
{
	long long x, y, r;

	if (m <= 1) {
		printf("Infinity\n");
		return;
	}

	x = ((t1.p * (m * m - 1)) / (t1.q * m * n)) + 1;
	y = ((t2.p * (m * m - 1)) / (t2.q * m * n));

	r = y - x + 1;
	if (r < 0) r = 0;

	printf("%lld\n", r);
}

long long gcd(long long x, long long y)
{
	int k;

	if (x < 0) x = -x;
	if (y < 0) y = -y;

	if (x > 0 && y > 0)
		for (k = 0; ((x | y) & 1LL) == 0LL; x >>= 1, y >>= 1, k++);
	else
		k = 0;

	for (;;) {
		if (x == 0LL) return (y << k);
		if (y == 0LL) return (x << k);

		while ((x & 1LL) == 0LL) x >>= 1;
		while ((y & 1LL) == 0LL) y >>= 1;

		if (x > y)
			x -= y;
		else
			y -= x;
	}
}

void reduce(rat_t *t)
{
	long long d;

	if (t->q < 0) {
		t->q = -t->q;
		t->p = -t->p;
	}

	d = gcd(t->p, t->q);

	t->p /= d;
	t->q /= d;
}

void get(rat_t *t)
{
	long long hr, mn, num, den;

	scanf("%lld : %lld %lld / %lld", &hr, &mn, &num, &den);

	if (den == 0) {
		num = 0;
		den = 1;
	}

	t->p = hr * n * den + mn * den + num;
	t->q = den;

	reduce(t);
}

int main()
{
	int t, q;

	for (t = 1; scanf("%lld %lld %d", &m, &n, &q) == 3; t++) {
		if (m == 0 || n == 0)
			break;

		printf("Planet %d:\n", t);

		while (q-- > 0) {
			get(&t1);
			get(&t2);

			solve();
		}
	}

	return 0;
}
