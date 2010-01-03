/*
ID: infnty1
PROB: comehome
LANG: C++
*/
#include <stdio.h>
#include <ctype.h>
#define INF 0x3FFFFFFF

int main()
{
	int d[64][64], a[64], b[256];
	int i, j, k, x, y, z, m;
	char c1, c2;;

	freopen("comehome.in", "r", stdin);
	freopen("comehome.out", "w", stdout);

	for (i = 0; i < 26; i++) b['A'+i]=i, b['a'+i]=26+i;
	for (i = 0; i < 64; i++) a[i] = 0;
	for (i = 0; i < 64; i++) { for (j = 0; j < 64; j++) d[i][j] = INF; d[i][i] = 0; }

	scanf("%d", &m);
	while (m-- > 0 && scanf(" %c %c %d", &c1, &c2, &z) == 3) {
		x = b[c1]; y = b[c2];
		if (z < d[x][y]) d[x][y] = d[y][x] = z;
	}

	for (k = 0; k < 52; k++)
		for (i = 0; i < 52; i++)
			for (j = i + 1; j < 52; j++)
				if (d[i][j] > d[i][k] + d[k][j])
					d[i][j] = d[j][i] = d[i][k] + d[k][j];

	for (i = 0, j = -1; i < 25; i++)
		if (d[i][25] < INF && (j < 0 || d[i][25] < d[j][25])) j = i;
	printf("%c %d\n", j+'A', d[j][25]);

	return 0;
}
