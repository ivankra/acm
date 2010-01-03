#include <stdio.h>

int x[131072], y[131072], z[131072], n;

int main()
{
	int i, j, k, a, b;

	for (n = 0; scanf("%d", &x[n]) == 1; n++);

	k = 1;
	z[1] = x[0];
	y[0] = 1;

	for (i = 1; i < n; i++) {
		if (x[i] > z[k]) {
			y[i] = ++k;
			z[k] = x[i];
			continue;
		}

		for (a = 1, b = k; (b - a) > 1;)
			if (z[j = (a + b) >> 1] < x[i])
				a = j + 1;
			else
				b = j;
		if (z[a] < x[i]) a++;

		y[i] = a;
		if (x[i] < z[a]) z[a] = x[i];
	}

	for (a = k, i = n - 1; y[i] != k; i--);

	for (z[--a] = j = x[i]; i >= 0; i--)
		if (y[i] == a && x[i] < j) z[--a] = j = x[i];

	printf("%d\n-\n", k);
	for (i = 0; i < k; i++)
		printf("%d\n", z[i]);

	return 0;
}
