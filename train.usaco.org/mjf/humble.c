/*
ID: mjf28791
PROG: humble
LANG: C
*/
#include <stdio.h>
#include <string.h>

#define INF (1LL << 62)

int main()
{
	static long long h[131072], a[128], s[128];
	int i, j, k, n;

	freopen("humble.in", "r", stdin);
	freopen("humble.out", "w", stdout);

	scanf("%d %d", &k, &n);
	for (i = 0; i < k; i++)
		scanf("%lld", &s[i]);

	memset(a, 0, sizeof(a));

	h[0] = 1;
	for (i = 1; i <= n; i++) {
		h[i] = INF;

		for (j = 0; j < k; j++) {
			while (h[a[j]] * s[j] <= h[i - 1])
				a[j]++;

			if (h[a[j]] * s[j] < h[i])
				h[i] = h[a[j]] * s[j];
		}
	}

	printf("%lld\n", h[n]);
	return 0;
}
