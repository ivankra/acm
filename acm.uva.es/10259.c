#include <stdio.h>

int a[128][128], b[128][128], n, k;

int max(int x, int y)
{
	return (x > y) ? x : y;
}

int f(int r, int c)
{
	int i;

	if (b[r][c] >= 0)
		return b[r][c];

	for (b[r][c] = 0, i = -k; i <= k; i++) {
		if (0 <= (r + i) && (r + i) < n && a[r + i][c] > a[r][c])
			b[r][c] = max(b[r][c], f(r + i, c));

		if (0 <= (c + i) && (c + i) < n && a[r][c + i] > a[r][c])
			b[r][c] = max(b[r][c], f(r, c + i));
	}

	return (b[r][c] += a[r][c]);
}

int main()
{
	int i, j, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &k) == 2;) {
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				b[i][j] = -1, scanf("%d", &a[i][j]);
		printf(t ? "%d\n\n" : "%d\n", f(0, 0));
	}

	return 0;
}
