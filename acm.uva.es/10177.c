#include <stdio.h>

long long pwr(long long a, int b)
{
	long long r = 1;

	while (b-- > 0)
		r *= a;

	return r;
}

int main()
{
	static long long hyp[8][128];
	int i, n;

	for (n = 1; n <= 4; n++)
		for (hyp[n][0] = 0, i = 1; i < 128; i++)
			hyp[n][i] = hyp[n][i - 1] + pwr(i, n);

	while (scanf("%d", &n) == 1)
		printf("%lld %lld %lld %lld %lld %lld\n",
			hyp[2][n], pwr(n * (n + 1) / 2, 2) - hyp[2][n],
			hyp[3][n], pwr(n * (n + 1) / 2, 3) - hyp[3][n],
			hyp[4][n], pwr(n * (n + 1) / 2, 4) - hyp[4][n]);

	return 0;
}
