#include <stdio.h>

char a[128][128];	/* m rows, n cols */
int n, m;

int hcheck(int y, int x, int l, int c)
{
	for (; l--; x++)
		if (a[y][x] != c) return 1;
	return 0;
}

int vcheck(int y, int x, int l, int c)
{
	for (; l--; y++)
		if (a[y][x] != c) return 1;
	return 0;
}

int sol(int y, int x)
{
	int s, c;

	if (y < 0 || x < 0 || y >= m || x >= n)
		return 0;

	c = a[y][x];

	for (s = 1; (y - s) >= 0 && (x - s) >= 0 && (y + s) < m && (x + s) < n; s++) {
		if (hcheck(y - s, x - s, 2 * s + 1, c) ||
		    hcheck(y + s, x - s, 2 * s + 1, c) ||
		    vcheck(y - s, x - s, 2 * s + 1, c) ||
		    vcheck(y - s, x + s, 2 * s + 1, c))
			break;
	}

	return 2 * s - 1;
}

int main()
{
	int i, j, k, q, t, y, x;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d %d", &m, &n, &q) == 3;) {
		printf("%d %d %d\n", m, n, q);

		for (i = 0; i < m; i++)
			for (j = 0; j < n && (k = getchar()) != EOF;)
				if (k != '\n' && k != '\r') a[i][j++] = k;

		while (q-- && scanf("%d %d", &y, &x) == 2)
			printf("%d\n", sol(y, x));
	}

	return 0;
}
