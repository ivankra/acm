/*
ID: mjf28791
PROG: comehome
LANG: C
*/
#include <stdio.h>

#define INF 0x3fffffff

int main()
{
	int d[64][64], map[256], i, j, k, m, z;
	char x, y;

	freopen("comehome.in", "r", stdin);
	freopen("comehome.out", "w", stdout);

	for (i = 0; i < 26; i++)
		map['A' + i] = i, map['a' + i] = 26 + i;

	for (i = 0; i < 52; i++)
		for (d[i][i] = 0, j = i + 1; j < 52; j++)
			d[i][j] = d[j][i] = INF;

	for (scanf("%d", &m); m-- > 0 && scanf(" %c %c %d", &x, &y, &z) == 3;)
		if (d[map[x]][map[y]] > z)
			d[map[x]][map[y]] = d[map[y]][map[x]] = z;

	for (k = 0; k < 52; k++)
		for (i = 0; i < 52; i++)
			for (j = i + 1; j < 52; j++)
				if ((d[i][k] + d[k][j]) < d[i][j])
					d[i][j] = d[j][i] = d[i][k] + d[k][j];

	for (k = i = 0; i < 25; i++)
		if (d[i][25] < d[k][25]) k = i;

	printf("%c %d\n", k + 'A', d[k][25]);
	return 0;
}
