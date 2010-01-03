#include <stdio.h>

#define swap(a, b) { int t = a; a = b; b = t; }

int a[128][128], n, m;

void apply1(int r)
{
	int i, j, h = n - 2 * r;

	for (i = 0; i < h; i++)
		swap(a[r][r + i], a[r + h - 1][r + i]);

	for (i = r + 1, j = r + h - 2; i < j; i++, j--) {
		swap(a[i][r], a[j][r]);
		swap(a[i][r + h - 1], a[j][r + h - 1]);
	}
}

void apply2(int r)
{
	int i, j, h = n - 2 * r;

	for (i = 0; i < h; i++)
		swap(a[r + i][r], a[r + i][r + h - 1]);

	for (i = r + 1, j = r + h - 2; i < j; i++, j--) {
		swap(a[r][i], a[r][j]);
		swap(a[r + h - 1][i], a[r + h - 1][j]);
	}
}

void apply3(int r)
{
	int i, h = n - 2 * r;

	for (i = 1; i < h; i++) {
		swap(a[r + i][r], a[r][r + i]);
		swap(a[r + h - 1][r + i], a[r + i][r + h - 1]);
	}
}

void apply4(int r)
{
	int i, h = n - 2 * r;

	for (i = 0; i < h; i++)
		swap(a[r][r + i], a[r + h - 1 - i][r + h - 1]);

	for (i = 1; i < h; i++)
		swap(a[r + i][r], a[r + h - 1][r + h - 1 - i]);
}

int main()
{
	int i, j, t, s, q;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				scanf("%d", &a[i][j]);

		m = (n + 1) / 2;

		for (i = 0; i < m && scanf("%d", &s) == 1; i++) {
			while (s-- > 0 && scanf("%d", &q) == 1) {
				if (q == 1) apply1(i);
				if (q == 2) apply2(i);
				if (q == 3) apply3(i);
				if (q == 4) apply4(i);
			}
		}

		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				printf(((j + 1) < n) ? "%d " : "%d\n", a[i][j]);
	}

	return 0;
}
