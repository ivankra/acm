#include <cstdio>

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		int n;
		long long c[100], d, k;

		scanf("%d", &n);
		for (int i = 0; i <= n; i++) scanf("%lld", &c[i]);
		scanf("%lld %lld", &d, &k);

		k = (k - 1) / d;

		long long x = 1;
		while (k >= x) { k -= x; x++; }

		long long y = 0;
		for (int i = n; i >= 0; i--) y = y * x + c[i];

		printf("%lld\n", y);
	}
}
