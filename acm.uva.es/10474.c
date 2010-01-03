#include <stdio.h>
#include <stdlib.h>

static void sort(int a[], int n)
{
	int i, j, p, t;

re:	if (n <= 32) {
		for (i = 1; i < n; i++) {
			for (t = a[i], j = i - 1; j >= 0 && a[j] > t; j--)
				a[j + 1] = a[j];
			a[j + 1] = t;
		}
		return;
	}

	p = a[n >> 1];

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
	static int *a, n, q, t, x;
	int i, low, up;

	for (t = 1; scanf("%d %d", &n, &q) == 2 && (n | q) > 0; t++) {
		a = (int *)malloc(n * sizeof(int) + 1024);

		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);

		sort(a, n);

		printf("CASE# %d:\n", t);

		while (q-- > 0 && scanf("%d", &x) == 1) {
			for (low = 0, up = n - 1; low < up;) {
				i = (low + up) >> 1;

				if (a[i] < x)
					low = i + 1;
				else if (a[i] > x)
					up = i - 1;
				else
					low = up = i;
			}

			if (low != up || a[low] != x) {
				printf("%d not found\n", x);
			} else {
				while (low > 0 && a[low - 1] == x) low--;
				printf("%d found at %d\n", x, low + 1);
			}
		}
	}

	return 0;
}
