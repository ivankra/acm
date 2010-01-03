#include <stdio.h>
#include <string.h>

long long bi[64][64], bi_rsum[64][64], bi_csum[64][64];

long long solve(long long n)
{
	long long r;
	int i, k;

	for (k = 0; bi_rsum[31][k] <= n; k++);

	if (k > 0)
		n -= bi_rsum[31][k - 1];

	for (r = 0; k > 0; k--) {
		for (i = k - 1; i < 30 && n >= bi_csum[i][k - 1]; i++);
		r |= (1LL << i);

		if (i > 0) n -= bi_csum[i - 1][k - 1];
	}

	return r;
}

void mktab()
{
	int i, j;

	memset(bi, 0, sizeof(bi));

	for (bi[0][0] = 1, i = 1; i <= 32; i++)
		for (bi[i][0] = 1, j = 1; j <= i; j++)
			bi[i][j] = bi[i - 1][j - 1] + bi[i - 1][j];

	memset(bi_rsum, 0, sizeof(bi_rsum));
	for (i = 0; i <= 32; i++)
		for (bi_rsum[i][0] = bi[i][0], j = 1; j <= 32; j++)
			bi_rsum[i][j] = bi_rsum[i][j - 1] + bi[i][j];

	memset(bi_csum, 0, sizeof(bi_csum));
	for (i = 0; i <= 32; i++)
		for (bi_csum[0][i] = bi[0][i], j = 1; j <= 32; j++)
			bi_csum[j][i] = bi_csum[j - 1][i] + bi[j][i];
}

int main()
{
	long long n;

	for (mktab(); scanf("%lld", &n) == 1;)
		printf("%lld\n", solve(n));

	return 0;
}
