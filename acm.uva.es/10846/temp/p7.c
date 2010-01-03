#include <stdio.h>
#include <stdlib.h>

typedef struct {
	long long p, q;
} rat_t;

long long m, n;
rat_t t1, t2;

void solve()
{
	long long k, r;

	if (m <= 1) {
		printf("0\n");
		return;
	}

	r = ((t2.p * (m * m - 1LL)) / (t2.q * m * n)) - ((t1.p * (m * m - 1LL)) / (t1.q * m * n));
	if (r < 0) r = 0;

	k = ((t2.p * (m - 1LL)) / (t2.q * m * n)) - ((t1.p * (m - 1LL)) / (t1.q * m * n));
	r -= k;
	if (r < 0) r = 0;

	printf("%lld\n", r);
}

void get(rat_t *t)
{
	long long hr, mn, num, den;

	scanf("%lld : %lld %lld / %lld", &hr, &mn, &num, &den);

	if (den <= 0) {
for(;;) malloc(10000);

		num = 0;
		den = 1;
	}

	t->p = hr * n * den + mn * den + num;
	t->q = den;
}

int main()
{
	int t, q;

	for (t = 1; scanf("%lld %lld %d", &m, &n, &q) == 3; t++) {
		if (m == 0 && n == 0 && q == 0)
			break;

		if (t != 1)
			printf("\n");

		printf("Planet %d:\n", t);

		while (q-- > 0) {
			get(&t1);
			get(&t2);

			solve();
		}
	}

	return 0;
}
