#include <stdio.h>
#include <stdlib.h>

static int x[1024], x2[1048576], n, n2;

static void sort(int a[], int n)
{
	int i, j, p, t;

re:	if (n < 32) {
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
		if (i >= j) break;
		t = a[i];
		a[i] = a[j];
		a[j] = t;
	}

	if ((n - i) > 1)
		sort(a + i, n - i);

	n = i;
	goto re;
}

static int find1(int r)
{
	register int a, b, c;
	for (a = 0, b = n - 1; a < b;) {
		c = (a + b) >> 1;
		if (x[c] > r)
			b = c - 1;
		else if (x[c] < r)
			a = c + 1;
		else
			return c;
	}
	return (x[a] == r) ? a : -1;
}

static int exists2(int r)
{
	register int a, b, c;
	for (a = 0, b = n2 - 1; a < b;) {
		c = (a + b) >> 1;
		if (x2[c] > r)
			b = c - 1;
		else if (x2[c] < r)
			a = c + 1;
		else
			return 1;
	}
	return (x2[a] == r);
}

static int find()
{
	int a, b, c, d, t;

	for (d = n - 1; d >= 0; d--) {
		for (c = n - 1; c >= 0; c--) {
			if (c == d) continue;

			t = x[d] - x[c];
			if (!exists2(t)) continue;

			for (a = 0; a < n; a++) {
				if (a == c || a == d) continue;
				b = find1(t - x[a]);
				if (b >= 0 && b != a && b != c && b != d)
					return d;
			}
		}
	}

	return -1;
}

static void make_x2()
{
	register int i, j, k;

	n2 = n * n;
	for (i = 0, k = 0; i < n; i++)
		for (j = 0; j < n; j++)
			x2[k++] = x[i] + x[j];

	sort(x2, n2);
}

int main()
{
	int i;

	while (scanf("%d", &n) == 1 && n != 0) {
		for (i = 0; i < n; i++)
			scanf("%d", &x[i]);

		sort(x, n);

		make_x2();

		i = find();

		if (i < 0)
			printf("no solution\n");
		else
			printf("%d\n", x[i]);
	}

	return 0;
}
