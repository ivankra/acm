#include <stdio.h>
#include <string.h>

long long tab[64][64], m;
int got[64][64];

long long f(long long n, long long k)
{
	long long r, i;

	if (n == 0 && k == 0)
		return 1;

	if (n < k || k <= 0)
		return 0;

	if (got[n][k]++)
		return tab[n][k];

	for (r = 0, i = 1; i <= m; i++)
		r += f(n - i, k - 1);

	return (tab[n][k] = r);
}

int main()
{
	long long n, k;

	while (scanf("%lld %lld %lld", &n, &k, &m) == 3) {
		memset(got, 0, sizeof(got));
		printf("%lld\n", f(n, k));
	}

	return 0;
}
