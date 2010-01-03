#include <stdio.h>
#include <stdlib.h>

int isqrt(int a)
{
	int x, y;

	for (x = a; x > 1; x = y)
		if ((y = (x + a / x) >> 1) >= x) break;

	return x;
}

int cmp(const void *p, const void *q)
{
	return *(int *)p - *(int *)q;
}

void solve(int n, int r)
{
	static int a[65536];
	int i, k, m;

	if (n < r || r < 0) return;

	for (k = 0, i = 1, m = isqrt(n) + 2; i <= m; i++)
		if ((n % i) == 0)
			a[k++] = i, a[k++] = n / i;

	qsort(a, k, sizeof(a[0]), &cmp);

	for (i = 0; i < k; i++)
		if (a[i] > r && (i == 0 || a[i - 1] != a[i]))
			printf(" %d", a[i]);
}

int main()
{
	int a, b, c, d;

	for (scanf("%d", &d), c = 1; c <= d && scanf("%d %d", &a, &b) == 2; c++) {
		printf("Case #%d:", c);
		if (a == b) { printf(" 0\n"); continue; }
		solve(a - b, b);
		printf("\n");
	}

	return 0;
}
