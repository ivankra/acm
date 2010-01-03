#include <stdio.h>

int a[16384], b[16384], inc[16384], dec[16384], n;

int min(int x, int y)
{
	return (x < y) ? x : y;
}

int solve()
{
	int i, j, k, t, p;

	if (n < 1)
		return 0;

	b[inc[0] = k = 1] = a[0];
	for (p = 1; p < n; p++) {
		if (a[p] > b[k]) {
			b[inc[p] = ++k] = a[p];
			continue;
		}

		for (i = 1, j = k; i < j;)
			if (b[t = (i + j) >> 1] < a[p]) i = t + 1; else j = t;
		inc[p] = i;
		if (a[p] < b[i]) b[i] = a[p];
	}

	b[dec[n - 1] = k = 1] = a[n - 1];
	for (p = n - 2; p >= 0; p--) {
		if (a[p] > b[k]) {
			b[dec[p] = ++k] = a[p];
			continue;
		}

		for (i = 1, j = k; i < j;)
			if (b[t = (i + j) >> 1] < a[p]) i = t + 1; else j = t;
		dec[p] = i;
		if (a[p] < b[i]) b[i] = a[p];
	}

	for (j = 1, i = 0; i < n; i++) {
		t = 2 * min(inc[i], dec[i]) - 1;
		if (t > j) j = t;
	}

	return j;
}

int main()
{
	int i;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);
		printf("%d\n", solve());
	}

	return 0;
}
