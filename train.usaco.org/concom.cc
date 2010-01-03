/*
ID: infnty1
PROB: concom
LANG: C++
*/
#include <stdio.h>
#include <string.h>

int con[128][128], shar[128][128];

int upd()
{
	static int s[128];
	int i, j, k, f=0;

	for (i = 1; i <= 100; i++) {
		for (j = 1; j <= 100; j++) s[j] = 0;

		for (j = 1; j <= 100; j++) {
			if (!con[i][j]) continue;
			for (k = 1; k <= 100; k++) s[k] += shar[j][k];
		}

		for (j = 1; j <= 100; j++)
			if (s[j]>50 && !con[i][j]) f++, con[i][j]=1;
	}

	return f;
}

int main()
{
	int m, x, y, p;

	freopen("concom.in", "r", stdin);
	freopen("concom.out", "w", stdout);

	memset(con, 0, sizeof(con));
	memset(shar, 0, sizeof(shar));

	for (scanf("%d", &m); m-- > 0 && scanf("%d %d %d", &x, &y, &p) == 3;)
		shar[x][y] += p;

	for (x = 1; x <= 100; x++)
		for (y = 1; y <= 100; y++)
			con[x][y] = (x==y || shar[x][y]>50);

	while (upd());

	for (x = 1; x <= 100; x++)
		for (y = 1; y <= 100; y++)
			if (x!=y && con[x][y]) printf("%d %d\n", x, y);

	return 0;
}
