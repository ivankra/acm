#include <stdio.h>

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

	for (p = a[(n - 1) >> 1], i = -1, j = n;;) {
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
	static int a[1024], s[1048576], k, n, m, t;
	int i, j, c, d;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);
		scanf("%d", &m);

		printf("Case %d:\n", t);

		for (k = 0, i = 0; i < n; i++)
			for (j = i + 1; j < n; j++)
				s[k++] = a[i] + a[j];
		sort(s, k);

		while (m-- > 0) {
			scanf("%d", &n);

			for (i = 0, j = k - 1; i < j;) {
				c = (i + j) >> 1;

				if (s[c] > n)
					j = c - 1;
				else if (s[c] < n)
					i = c + 1;
				else
					i = j = c;
			}

			if (i > 0) i--;
			if (j < (k - 1)) j++;

			c = s[i++];
			d = (c >= n) ? (c - n) : (n - c);

			for (; i <= j; i++) {
				register int x;
				x = (s[i] >= n) ? (s[i] - n) : (n - s[i]);
				if (x < d) {
					c = s[i];
					d = x;
				}
			}

			printf("Closest sum to %d is %d.\n", n, c);
		}
	}

	return 0;
}
