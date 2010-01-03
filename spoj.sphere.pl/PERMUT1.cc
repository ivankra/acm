#include <cstdio>
#include <cstring>

int main()
{
	long long f[16][128];

	memset(f, 0, sizeof(f));
	f[0][0] = 1;

	for (int n = 1; n <= 12; n++)
		for (int k = 0; k <= n*(n-1)/2; k++)
			for (int i = 0; i < n && k-i >= 0; i++)
				f[n][k] += f[n-1][k-i];

	int t, n, k;
	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &k) == 2;)
		printf("%lld\n", f[n][k]);
}
