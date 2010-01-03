#include <stdio.h>
#include <string.h>

int main()
{
	static long long f[32][160], p, q;
	int n, k, x;

	memset(f, 0, sizeof(f));
	f[0][0] = 1;

	for (n = 1; n <= 24; n++)
		for (x = 1; x <= 150; x++)
			for (k = 1; k <= 6; k++)
				if ((x - k) >= 0) f[n][x] += f[n - 1][x - k];

	while (scanf("%d %d", &n, &x) == 2 && n > 0) {
		for (p = 0, k = x; k <= 150; k++)
			p += f[n][k];
		for (q = 1; n-- > 0; q *= 6LL);

		while ((p % 2LL) == 0 && (q % 2LL) == 0)
			p /= 2LL, q /= 2LL;

		while ((p % 3LL) == 0 && (q % 3LL) == 0)
			p /= 3LL, q /= 3LL;

		printf((q == 1LL) ? "%lld\n" : "%lld/%lld\n", p, q);
	}

	return 0;
}
