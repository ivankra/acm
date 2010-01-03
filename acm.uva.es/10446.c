#include <stdio.h>

int main()
{
	static unsigned long long a[64][64];
	int i, n, k;

	for (n = 0; n <= 1; n++)
		for (k = 0; k <= 60; k++) a[n][k] = 1;

	for (n = 2; n <= 60; n++)
		for (k = 0; k <= 60; k++)
			for (a[n][k] = 1, i = 1; i <= k; i++)
				a[n][k] += ((n - i) >= 0) ? a[n - i][k] : 1;

	for (i = 1; scanf("%d %d", &n, &k) == 2 && n <= 60; i++) {
		if (n <= 1 || k < 1)
			printf("Case %d: 1\n", i);
		else
			printf("Case %d: %llu\n", i, a[n][k]);
	}

	return 0;
}
