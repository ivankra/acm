/*
ID: mjf28791
PROG: concom
LANG: C
*/
#include <stdio.h>
#include <string.h>

int owns[128][128], shares[128][128], map1[128], map2[128], n;
int c[128][128];

int update()
{
	int i, j, k, u;

	for (u = 0, i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (owns[i][j] || c[i][j] <= 50)
				continue;

			u = 1;
			owns[i][j] = 1;

			for (k = 0; k < n; k++)
				c[i][k] += shares[j][k];
		}
	}

	return u;
}

int main()
{
	int i, m, x, y, z;

	freopen("concom.in", "r", stdin);
	freopen("concom.out", "w", stdout);

	memset(owns, 0, sizeof(owns));
	memset(shares, 0, sizeof(shares));
	memset(c, 0, sizeof(c));

	for (i = 0; i < 128; i++)
		map1[i] = -1;

	scanf("%d", &m);
	while (m-- > 0 && scanf("%d %d %d", &x, &y, &z) == 3) {
		if (map1[x] < 0) map1[x] = n++;
		if (map1[y] < 0) map1[y] = n++;
		shares[map1[x]][map1[y]] = z;
		c[map1[x]][map1[y]] = z;
	}

	for (i = 0; i < 128; i++)
		map2[map1[i]] = i;

	for (i = 0; i < n; i++)
		owns[i][i] = 1;

	while (update());

	for (x = 0; x < 128; x++) {
		if (map1[x] < 0) continue;
		for (y = 0; y < 128; y++) {
			if (x == y || map1[y] < 0) continue;
			if (owns[map1[x]][map1[y]])
				printf("%d %d\n", x, y);
		}
	}

	return 0;
}
