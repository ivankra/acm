#include <stdio.h>
#include <stdlib.h>

static void sort(float a[], int n)
{
	float v, t;
	int i, j;

re:
	if (n < 24) {
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
	static float s[10010];	
	float r;
	register int i;
	int f, k, n, h, t;

	scanf("%d", &t);

	while (t-- > 0) {
		scanf("%d", &n);

		for (i = 0; i < n; i++)
			scanf("%d %d", &x[i], &y[i]);
		if (x[n - 1] != x[n] || y[n - 1] != y[n])
			x[n] = x[0], y[n] = y[0];

		scanf("%d %d", &h, &f);

		for (i = 1, k = 0; i <= n; i++) {
			if (x[i - 1] == x[i] /*|| x[i] == f || x[i - 1] == f*/)
				continue;

			if ((x[i] <= f && x[i - 1] <= f) ||
			    (x[i] >= f && x[i - 1] >= f))
				continue;

			s[k++] =
			   ( (((float)y[i - 1] - (float)y[i]) * (float)f)
			     + ((float)x[i - 1] * (float)y[i])
			     - ((float)y[i - 1] * (float)x[i])
 			   ) / ((float)x[i - 1] - (float)x[i]);
		}

		if (k > 1)
			sort(s, k);

		for (i = 1, r = 0.0; i < k; i += 2)
			r += s[i] - s[i - 1];

		printf(r >= ((float)h - 0.0001) ? "YES\n" : "NO\n");
	}

	return 0;
}
