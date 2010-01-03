#include <stdio.h>
#include <assert.h>

typedef long long num;

num min(num a, num b) { return (a < b) ? a : b; }

num f(num n, num m)
{
	num k;

	if (m >= n)
		return n;

	if (n == 1)
		return 1;

	for (k = min(m, n); k >= 2; k--)
		if ((n % k) == 0 && ((n - 1) % (k - 1)) == 0) return k;

	return 0;
}

int main()
{
	num n, k, m;

	while (scanf("%lld %lld", &n, &m) == 2) {
		assert(n < 0x100000000LL);
		assert(m < 0x100000000LL);

		k = f(n, m);

		if (k == 1 && n > 1)
			k = 0;

		if (k == 0)
			printf("No solution\n");
		else if (k == 1)
			printf("1 persons/group, 1 day\n");
		else
			printf("%lld persons/group, %lld day%s\n",
				k, (n - 1) / (k - 1), (n == k) ? "" : "s");
	}

	return 0;
}
