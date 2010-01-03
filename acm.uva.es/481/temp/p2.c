#include <stdio.h>

/*
   x[i]: the input
   y[i]: the length of LIS, ending at x[i]
   z[i]: the smallest integer with which an LIS of length i may ends

*/

int x[131072], y[131072], z[131072], n, k;

int main()
{
	int i, j, a, b;

	for (n = 0; scanf("%d", &x[n]) == 1; n++);

	k = 1;
	z[0] = -0x7FFFFFFF;
	z[1] = x[0];
	y[0] = 1;

	for (i = 1; i < n; i++) {
		for (j = 1; j <= k && z[j] < x[i]; j++);

		y[i] = j;
		if (j > k) {
			z[j] = x[i];
			k = j;
		} else {
			if (x[i] < z[j]) z[j] = x[i];
		}
	}

	for (i = n - 1, a = k, j = 0x7FFFFFFF; i >= 0; i--)
		if (y[i] == a && x[i] < j)
			z[--a] = j = x[i];

	printf("%d\n-\n", k);
	for (i = 0; i < k; i++)
		printf("%d\n", z[i]);

	return 0;
}
