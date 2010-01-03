#include <stdio.h>

int main()
{
	long long c[32], i, n;

	for (c[0] = n = 1; n < 32; n++)
		for (c[n] = 0, i = 0; i < n; i++) c[n] += c[i] * c[n - 1 - i];

	while (scanf("%lld", &n) == 1) {
		for (i = 1; c[i] < n; i++);
		printf("%lld\n", i);
	}

	return 0;
}
