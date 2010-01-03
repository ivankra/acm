#include <stdio.h>
#include <stdlib.h>

void sort(int a[], int n)
{
	int i, j, p, t;

re:
	if (n < 32) {
		for (i = 1; i < n; i++) {
			for (t = a[i], j = i - 1; j >= 0 && a[j] > t; j--)
				a[j + 1] = a[j];
			a[j + 1] = t;
		}
		return;
	}

	for (p = a[n >> 1], i = -1, j = n;;) {
		while (a[++i] < p);
		while (a[--j] > p);

		if (i >= j)
			break;

		t = a[i];
		a[i] = a[j];
		a[j] = t;
	}

	sort(a + i, n - i);

	n = i;
	goto re;
}

int main()
{
	static int x[65536], y[65536], n, t;
	int i;

	for (scanf("%d", &t); t-- > 0 && scanf("%*d %*d %d", &n) == 1;) {
		for (i = 0; i < n; i++)
			scanf("%d %d", &x[i], &y[i]);

		sort(x, n);
		sort(y, n);

		printf("(Street: %d, Avenue: %d)\n",
			x[(n - 1) >> 1], y[(n - 1) >> 1]);
	}

	return 0;
}
