#include <stdio.h>
#include <assert.h>

typedef long long num;

num xabs(num x) { return (x < 0) ? -x : x; }

num f(num x)
{
	num r, d, e;

	for (r = 1, d = 2; d < 1000; d++) {
		for (e = 1; (x % d) == 0; e++, x /= d);
		r *= e;
	}

	return r;
}

int main()
{
	num t, m, n, p;

	for (t = 1; scanf("%lld %lld %lld", &m, &n, &p) == 3 && p != 0; t++)
		printf("Case %lld: %lld\n", t, 2 * f(xabs(m * n * p * p)) - 1);

	return 0;
}
