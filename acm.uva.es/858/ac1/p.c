#include <stdio.h>
#include <stdlib.h>

static void sort(double a[], int n)
{
	double v, t;
	int i, j;

re:
	if (n < 8) {
		for (i = 1; i < n; i++) {
			for (t = a[i], j = i - 1; j >= 0 && a[j] > t; j--)
				a[j + 1] = a[j];
			a[j + 1] = t;
		}
		return;
	}

	v = a[n >> 1];
	for (i = -1, j = n;;) {
		while (a[++i] < v);
		while (a[--j] > v);
		if (i >= j) break;
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
	static int x[10010], y[10010];
	static double s[10010], r;
	int t, n, h, f, i, k;

	scanf("%d", &t);

	while (t-- > 0) {
		scanf("%d", &n);

		for (i = 0; i < n; i++)
			scanf("%d %d", &x[i], &y[i]);
		if (x[n - 1] != x[n] || y[n - 1] != y[n])
			x[n] = x[0], y[n] = y[0];

		scanf("%d %d", &h, &f);

		for (i = 1, k = 0; i <= n; i++) {
			if (x[i - 1] == x[i] || x[i] == f || x[i - 1] == f)
				continue;

			if ((x[i] <= f && x[i - 1] <= f) ||
			    (x[i] >= f && x[i - 1] >= f))
				continue;

			s[k++] =
			   ( (((double)y[i - 1] - (double)y[i]) * (double)f)
			     + ((double)x[i - 1] * (double)y[i])
			     - ((double)y[i - 1] * (double)x[i])
 			   ) / ((double)x[i-1] - (double)x[i]);
		}

		sort(s, k);

		for (i = 1, r = 0.0; i < k; i += 2)
			r += s[i] - s[i - 1];

		printf(r >= ((double)h - 0.0001) ? "YES\n" : "NO\n");
	}

	return 0;
}
