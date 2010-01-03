#include <stdio.h>

void sort(int a[], int n)
{
	int i, j, t, p;

re:	if (n < 32) {
		for (i = 1; i < n; i++) {
			for (t = a[i], j = i - 1; j >= 0 && a[j] > t; j--)
				a[j + 1] = a[j];
			a[j + 1] = t;
		}
		return;
	}

	p = a[(n + 1) >> 1];

	for (i = -1, j = n;;) {
		while (a[++i] < p);
		while (a[--j] > p);

		if (i >= j)
			break;

		t = a[i];
		a[i] = a[j];
		a[j] = t;
	}

	if ((n - i) > 1)
		sort(a + i, n - i);

	n = i;
	goto re;
}

int main()
{
	int a[512], n, t, r, i, j;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);

		sort(a, n);

		j = (n >> 1);

		for (r = 0, i = 0; i < j; i++)
			r += a[j] - a[i];

		for (; i < n; i++)
			r += a[i] - a[j];

		printf("%d\n", r);
	}

	return 0;
}
