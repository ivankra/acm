/*
ID: infnty1
PROB: range
LANG: C++
*/
#include <stdio.h>

int a[256][256], b[256][256], c[256], n;

int main()
{
	int i, j, k;

	freopen("range.in", "r", stdin);
	freopen("range.out", "w", stdout);

	scanf("%d", &n);
	for (i = 0; i < n; i++)
		for (j = 0; j < n && (k = getchar()) != EOF;)
			if (k == '0' || k == '1') a[i][j++] = k-'0';

	for (i = 0; i < n; i++) {
		b[0][i] = a[0][i];
		b[i][0] = a[i][0];
	}

	for (i = 1; i < n; i++) {
		for (j = 1; j < n; j++) {
			if (a[i][j] == 0) {
				b[i][j] = 0;
			} else {
				k = b[i-1][j] <? b[i][j-1];
				b[i][j] = a[i-k][j-k] ? (k+1) : k;
			}
		}
	}

	for (i = 0; i <= n; i++) c[i] = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			c[b[i][j]]++;

	for (i = n; i > 0; i--)
		c[i-1] += c[i];

	for (i = 2; i <= n && c[i] > 0; i++)
		printf("%d %d\n", i, c[i]);

	return 0;
}
