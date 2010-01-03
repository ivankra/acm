#include <stdio.h>
#include <string.h>
#include <assert.h>

#define INF 0x1FFFFFFF

typedef struct { int x, y; } pair_t;

int cost[16][16], tab[65536], n;

int wall[64][64], width, height;
pair_t boxp[16], goalp[16];

int find(int p, int m)
{
	int i, t;

	if (tab[m] >= 0)
		return tab[m];

	for (tab[m] = INF, i = 0; i < n; i++) {
		if (((m >> i) & 1) == 0) {
			t = cost[p][i] + find(p + 1, m | (1 << i));
			if (t < tab[m]) tab[m] = t;
		}
	}

	return tab[m];
}

pair_t mkpair(int x, int y)
{
	pair_t p;
	p.x = x;
	p.y = y;
	return p;
}

void bfs(int id)
{
	static pair_t q[4096];
	static int d[64][64];
	int i, j, h, t;

	for (i = 1; i <= height; i++)
		for (j = 1; j <= width; j++)
			d[i][j] = INF;

	h = t = 0;
	q[t++] = boxp[id];
	d[boxp[id].y][boxp[id].x] = 0;

	for (; h < t; h++) {
		for (i = 0; i < 4; i++) {
			q[t].y = q[h].y + "1102"[i] - '1';
			q[t].x = q[h].x + "0211"[i] - '1';
			if (!wall[q[t].y][q[t].x] &&
			    d[q[t].y][q[t].x] > (d[q[h].y][q[h].x] + 1)) {
				d[q[t].y][q[t].x] = d[q[h].y][q[h].x] + 1;
				t++;
			}
		}
	}

	for (i = 0; i < n; i++)
		cost[id][i] = d[goalp[i].y][goalp[i].x];
}

int main()
{
	int i, j, c, g, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &height, &width) == 2;) {
		for (i = 0; i <= (height + 1); i++)
			for (j = 0; j <= (width + 1); j++)
				wall[i][j] = 1;

		for (i = 1, n = g = 0; i <= height; i++) {
			for (j = 1; j <= width && (c = getchar()) != EOF;) {
				if (c == '#') {
					j++;
				} else if (c == '.') {
					wall[i][j++] = 0;
				} else if (c == 'B') {
					boxp[n++] = mkpair(j, i);
					wall[i][j++] = 0;
				} else if (c == 'X') {
					goalp[g++] = mkpair(j, i);
					wall[i][j++] = 0;
				}
			}
		}

		assert(n == g && n <= 16);

		for (i = 0; i < n; i++)
			bfs(i);

		for (i = 0, j = (1 << n); i < j; i++)
			tab[i] = -1;
		tab[j - 1] = 0;

/*for (i=0;i<n;i++){for(j=0;j<n;j++)printf(" %4d",cost[i][j]==INF?-1:cost[i][j]);printf("\n");}printf("\n");*/

		printf("%d\n", find(0, 0));
	}

	return 0;
}
