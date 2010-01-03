#include <cstdio>
#include <cstring>
#define INF 0x3fffffff
int map[256][256], dist[256][256][2], n, m, qu[256*256*2+10], *qh, *qt;

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (;;) {
				map[i][j] = getchar();
				if (strchr(".FW", map[i][j])) break;
			}
			dist[i][j][0] = dist[i][j][1] = INF;
		}
	}

	dist[0][0][0] = 0;
	qh = qu; qt = qu; *qt++ = 0;
	for (; qh < qt; qh++) {
		int y = (*qh)>>9, x = ((*qh)>>1)&0xff, s=(*qh)&1;
		if (y == n-1 && x == m-1) {
			printf("%d\n", dist[y][x][s]);
			return 0;
		}
		for (int d = 0; d < 4; d++) {
			int y1 = y + "1102"[d] - '1';
			int x1 = x + "0211"[d] - '1';
			if (x1 < 0 || x1 >= m || y1 < 0 || y1 >= n) continue;
			if (s == 0 && map[y1][x1] == 'F') continue;
			if (s == 1 && map[y1][x1] == 'W') continue;
			int s1 = s;
			if (map[y1][x1] == 'F') s1 = 0;
			else if (map[y1][x1] == 'W') s1 = 1;
			if (dist[y1][x1][s1] < INF) continue;
			dist[y1][x1][s1] = dist[y][x][s] + 1;
			*qt++ = (y1<<9)|(x1<<1)|s1;
		}
	}
	printf("No solution.\n");
}
