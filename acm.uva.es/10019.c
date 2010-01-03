#include <stdio.h>

int main()
{
	int t, n, k, r1, r2;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (k = n, r1 = 0; k; k >>= 1)
			r1 += (k & 1);

		for (k = 0; n; n /= 10)
			k = (k << 4) | (n % 10);

		for (r2 = 0; k; k >>= 1)
			r2 += (k & 1);

		printf("%d %d\n", r1, r2);
	}

	return 0;
}
