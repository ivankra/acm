#include <stdio.h>
#include <assert.h>

typedef long long num;

num xabs(num x) { return (x < 0) ? -x : x; }

int prime[4096];

void sieve()
{
	static char s[1024];
	int i, j;

	memset(s, 0, sizeof(s));

	for (i = 2; i < 34; i++)
		if (s[i] == 0)
			for (j = i * i; j < 1024; j += i) s[j] = 1;

	for (i = 2, j = 0; i < 1024; i++)
		if (s[i] == 0) prime[j++] = i;
}

num f(num x)
{
	num r, d, e;
	int i;

	for (r = 1, i = 0; (prime[i] * prime[i]) <= x; i++) {
		d = prime[i];
		for (e = 1; (x % d) == 0; e++, x /= d);
		r *= e;
	}

	if (x > 1) r *= 2;

	return r;
}

int main()
{
	num t, m, n, p;

	sieve();
	for (t = 1; scanf("%lld %lld %lld", &m, &n, &p) == 3 && p != 0; t++)
		printf("Case %lld: %lld\n", t, 2 * f(xabs(m * n * p * p)) - 1);

	return 0;
}
