#include <stdio.h>
#include <stdlib.h>

typedef struct {
	long long p, q;
} rat_t;

long long m, n;
rat_t t1, t2;

void solve()
{
	long long k, kmax, r;
	rat_t z;

	if (m <= 1) {
		printf("0\n");
		return;
	}

	k = ((t1.p * (m * m - 1)) / (t1.q * m * n)) + 1;
	kmax = ((t2.p * (m * m - 1)) / (t2.q * m * n));

printf("k=%lld .. %lld\n", k, kmax);

	for (r = 0; k <= kmax; k++) {
		z.p = m * n * k;
		z.q = m * m - 1;
printf(" %lld/%lld [%.5f]", z.p, z.q, (double)z.p / (double)z.q);

		printf("{%d}", k % (m + 1));

	}
printf("\n");

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
