/*
ID: mjf28791
PROG: sort3
LANG: C
*/
#include <stdio.h>
#include <string.h>

int min(int x, int y)
{
	return (x < y) ? x : y;
}

int main()
{
	static int a[1024], b[1024], c[4][4];
	int i, j, k, n, r;

	freopen("sort3.in", "r", stdin);
	freopen("sort3.out", "w", stdout);

	memset(c, 0, sizeof(c));

	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		c[0][a[i]]++;
	}

	for (i = 0, j = 1; j <= 3; j++)
		for (k = 0; k < c[0][j]; k++) b[i++] = j;

	for (i = 0; i < n; i++)
		c[a[i]][b[i]]++;

	r = (k = min(c[1][2], c[2][1]));
	c[1][2] -= k;
	c[2][1] -= k;

	r += (k = min(c[1][3], c[3][1]));
	c[1][3] -= k;
	c[3][1] -= k;

	r += (k = min(c[2][3], c[3][2]));
	c[2][3] -= k;
	c[3][2] -= k;

	printf("%d\n", r + 2 * (c[1][2] + c[2][1]));

	return 0;
}
