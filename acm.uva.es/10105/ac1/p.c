#include <stdio.h>

int main()
{
	int f[16], i, n, k, a, r;

	for (f[0] = 1, i = 1; i <= 12; i++)
		f[i] = i * f[i - 1];

	while (scanf("%d %d", &n, &k) == 2) {
		for (r = f[n], i = 0; i < k && scanf("%d", &a) == 1; i++)
			r /= f[a];
		printf("%d\n", r);
	}

	return 0;
}
