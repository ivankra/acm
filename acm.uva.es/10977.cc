#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 0x3FFFFFFF

int R, C, map[256][256], dist[256][256], qy[65536], qx[65536], qh, qt;

int solve()
{
	if (map[1][1] || map[R][C]) return -1;

	for (int i = 0; i <= R+1; i++)
		for (int j = 0; j <= C+1; j++)
			dist[i][j] = INF;
	dist[1][1] = 0;

	qh = 0;
	qt = 1;
	qy[0] = qx[0] = 1;

	for (; qh < qt; qh++) {
		for (int i = 0; i < 4; i++) {
			int y = qy[qh] + "1210"[i] - '1';
			int x = qx[qh] + "2101"[i] - '1';
			if (map[y][x] || dist[y][x] < INF) continue;
			dist[y][x] = dist[qy[qh]][qx[qh]] + 1;
			qy[qt]=y; qx[qt++] = x;
		}
	}

	return (dist[R][C] < INF) ? dist[R][C] : -1;
}

int main()
{
	while (scanf("%d %d", &R, &C) == 2&& R > 0) {
		memset(map, 0, sizeof(map));
		int m, y, x, l;
		scanf("%d", &m);
		while (m-- > 0 && scanf("%d %d", &y, &x) == 2) map[y][x] = 1;
		for (int i = 0; i <= C+1; i++) map[0][i]=map[R+1][i]=1;
		for (int i = 0; i <= R+1; i++) map[i][0]=map[i][C+1]=1;
		scanf("%d", &m);
		while (m-- > 0 && scanf("%d %d %d", &y, &x, &l) == 3) {
			for (int i = -l; i <= l; i++) {
				if (y+i <= 0 || y+i > R) continue;
				for (int j = -l; j <= l; j++) {
					if (x+j <= 0 || x+j > C) continue;
					if ((abs(i)*abs(i) + abs(j)*abs(j)) > l*l) continue;
					map[y+i][x+j] = 1;
				}
			}	
		}

		int i = solve();
		if (i < 0) printf("Impossible.\n"); else printf("%d\n", i);
	}

	return 0;
}
