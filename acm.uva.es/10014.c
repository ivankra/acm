#include <stdio.h>

static double a0, an1, c[4096];
static int n;

static double solve(void)
{
	double p, q, r, t;
	int k;

	p = 2;
	q = -1;
	r = 2 * c[n];
	for (k = 0; k < (n - 1); k++) {
		t = 2 * p + q;
		q = -p;
		r = r + 2 * p * c[n - k - 1];
		p = t;
	}

	return (an1 - q * a0 - r) / p;
}

int main(void)
{
	int s, i;

	scanf("%d", &s);
	while (s-- > 0) {
		scanf("%d %lf %lf", &n, &a0, &an1);
		c[0] = 0;
		for (i = 1; i <= n; i++)
			scanf("%lf", &c[i]);

		printf("%.2f\n", solve());
		if (s != 0) printf("\n");
	}

	return 0;
}
