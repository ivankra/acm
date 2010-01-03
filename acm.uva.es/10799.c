#include <stdio.h>

long long low, high, k;

long long solve()
{
	long long n, u;

	n = high - low + 1;

	if (k == 1)
		return n;

	if ((k & 1) == 0) {
		u = n / (2 * k - 2);
		return u * (n + (1 - k) * (u + 1));
	} else {
		u = n / (k - 1);
		return u * (2 * n + (1 - k) * (u + 1)) / 2;
	}
}

int main()
{
	int t;

	for (t = 1; scanf("%lld %lld %lld", &low, &high, &k) == 3 && k > 0;)
		printf("Case %d: %lld\n", t++, solve());

	return 0;
}
