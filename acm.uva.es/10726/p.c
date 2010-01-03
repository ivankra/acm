#include <stdio.h>

long long pw(long long a, long long b)
{
	long long r;

	for (r = 1; b > 0; b >>= 1) {
		if ((b & 1) != 0)
			r *= a;

		a *= a;
	}

	return r;
}

long long solve()
{
	long long a, b, c, s, m, u, r;

	scanf("%lld %lld %lld %lld", &s, &m, &a, &b);

	if (s >= 11)
		return 0;

	u = pw(s, s + 1);
	c = -m * pw(-s, s) + m - m * s;

	while (c < a)
		c += u;

	for (r = 0; c <= b; c += u)
		r++;

	return r;
}

int main()
{
	int c, t;

	for (scanf("%d", &t), c = 1; c <= t; c++)
		printf("Case %d: %lld\n", c, solve());

	return 0;
}
